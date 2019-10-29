import functools
import os
import typing


def read_nt_string(fp):
    s = b''
    while not s.endswith(b'\0'):
        s += fp.read(1)
    return s[:-1].decode()


class ProgramHeader:
    def __init__(self, eh):
        self.p_type = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        if eh.intwidth == 2:
            self.p_flags = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.p_offset = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.p_vaddr = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.p_paddr = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.p_filesz = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.p_memsz = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        if eh.intwidth == 1:
            self.p_flags = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.p_align = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)

    def __repr__(self):
        return f'ProgramHeader(0x{self.p_vaddr:08x})'


class SectionHeader:
    def __init__(self, eh):
        self.sh_name = None
        self.sh_name_off = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.sh_type = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.sh_flags = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.sh_addr = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.sh_offset = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.sh_size = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.sh_link = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.sh_info = int.from_bytes(eh.read(4), eh.endianness, signed=False)
        self.sh_addralign = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        self.sh_entsize = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)

    def __repr__(self):
        if self.sh_name is None:
            return f'SectionHeader(anon@0x{self.sh_addr:08x})'
        else:
            return f'SectionHeader({self.sh_name}@0x{self.sh_addr:08x})'


@functools.total_ordering
class Symbol:
    def __init__(self):
        self.st_name = None
        self.st_sh = None
        self.st_name_off = 0
        self.st_value = 0
        self.st_size = 0
        self.st_info = 0
        self.st_other = 0
        self.st_shndx = -1

    def __repr__(self):
        if self.st_name is None:
            return f'Symbol(anon0x{self.st_value})'
        else:
            return f'Symbol({self.st_name}@0x{self.st_value:08x})'

    def __eq__(self, other):
        if isinstance(other, str):
            return self.st_name == other
        if isinstance(other, self.__class__):
            return self.st_name == other.st_name and self.st_value == other.st_value
        if isinstance(other, int):
            return self.st_value == other
        return NotImplemented

    def __lt__(self, other):
        if isinstance(other, self.__class__):
            return self.st_value < other.st_value
        if isinstance(other, int):
            return self.st_value < other
        return NotImplemented

    @classmethod
    def from_eh(cls, eh):
        self = cls()
        self.st_name_off = int.from_bytes(eh.read(4 * eh.intwidth), eh.endianness, signed=False)
        if eh.intwidth == 1:
            self.st_value = int.from_bytes(eh.read(4), eh.endianness, signed=False)
            self.st_size = int.from_bytes(eh.read(4), eh.endianness, signed=False)
            self.st_info = int.from_bytes(eh.read(1), eh.endianness, signed=False)
            self.st_other = int.from_bytes(eh.read(1), eh.endianness, signed=False)
            self.st_shndx = int.from_bytes(eh.read(2), eh.endianness, signed=False)
        else:
            self.st_info = int.from_bytes(eh.read(1), eh.endianness, signed=False)
            self.st_other = int.from_bytes(eh.read(1), eh.endianness, signed=False)
            self.st_shndx = int.from_bytes(eh.read(2), eh.endianness, signed=False)
            self.st_value = int.from_bytes(eh.read(8), eh.endianness, signed=False)
            self.st_size = int.from_bytes(eh.read(8), eh.endianness, signed=False)
        return self

    def __bool__(self):
        return self.st_name is not None


class Elf:
    # Only for ARM32LEv1
    def __init__(self, fp):
        self._fp = fp
        print('Reading ELF file:', fp.name, '... ', end='', flush=True)
        assert self._fp.read(4) == b'\x7fELF'
        self.intwidth = int.from_bytes(self._fp.read(1), 'little', signed=False)
        self.endianness = 'little' if self._fp.read(1) == b'\x01' else 'big'
        self.version = int.from_bytes(self._fp.read(1), 'little', signed=False)
        self.abi = int.from_bytes(self._fp.read(1), 'little', signed=False)
        self.abiver = int.from_bytes(self._fp.read(1), 'little', signed=False)
        self._fp.seek(16)
        self.obj_filetype = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.machine = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.eversion = int.from_bytes(self._fp.read(4), self.endianness, signed=False)
        self.e_entry = int.from_bytes(self._fp.read(self.intwidth * 4), self.endianness, signed=False)
        self.e_phoff = int.from_bytes(self._fp.read(self.intwidth * 4), self.endianness, signed=False)
        self.e_shoff = int.from_bytes(self._fp.read(self.intwidth * 4), self.endianness, signed=False)
        self.e_flags = int.from_bytes(self._fp.read(4), self.endianness, signed=False)
        self.e_ehsize = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.e_phentsize = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.e_phnum = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.e_shentsize = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.e_shnum = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        self.e_shstrndx = int.from_bytes(self._fp.read(2), self.endianness, signed=False)
        print('done')

        print('Reading program headers... ', end='', flush=True)
        self._fp.seek(self.e_phoff)
        self.program_headers: typing.List[ProgramHeader] = [ProgramHeader(self) for i in range(self.e_phnum)]
        print('done')

        print('Reading section headers... ', end='', flush=True)
        self._fp.seek(self.e_shoff)
        self.section_headers: typing.List[SectionHeader] = [SectionHeader(self) for i in range(self.e_shnum)]
        self.shstrtab = self.section_headers[self.e_shstrndx]
        print('done')

        print('Reading symbols and strings... ', end='', flush=True)
        self.strings: typing.Dict[bool, typing.Dict[int, str]] = {}
        self.symbols: typing.List[Symbol] = []
        strconcat = ''
        shstrconcat = ''
        for i, strtab in enumerate(self.section_headers):
            if strtab.sh_type == 3:  # string table
                self._fp.seek(strtab.sh_offset)
                is_shstr = i == self.e_shstrndx
                self.strings[is_shstr] = {}
                while self._fp.tell() < strtab.sh_offset + strtab.sh_size:
                    off = self._fp.tell() - strtab.sh_offset
                    s = read_nt_string(self._fp)
                    if is_shstr:
                        shstrconcat += s + '\0'
                    else:
                        strconcat += s + '\0'
                    self.strings[is_shstr][off] = s
            elif strtab.sh_type == 2:  # symbol table
                self._fp.seek(strtab.sh_offset)
                while self._fp.tell() < strtab.sh_offset + strtab.sh_size:
                    self.symbols.append(Symbol.from_eh(self))
        print('done')

        print('Assigning section names... ', end='', flush=True)
        for sec in self.section_headers:
            s = shstrconcat[sec.sh_name_off:]
            sec.sh_name = s[:s.find('\0')]
        print('done')

        print('Assigning symbol names... ', end='', flush=True)
        for i, sym in enumerate(self.symbols):
            s = strconcat[sym.st_name_off:]
            sym.st_name = s[:s.find('\0')]
            if sym.st_shndx < 0xFF00:
                sym.st_sh = self.section_headers[sym.st_shndx]
        self.symbols_sorted = sorted(self.symbols)
        print('done')

    def __enter__(self):
        return self

    def close(self):
        self._fp.close()
        self._fp = None

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()

    def get_sym(self, name) -> typing.Union[None, Symbol]:
        for sym in self.symbols:
            if sym == name:
                return sym
        # print(f'WARNING: symbol {name} not found, returning dummy object')
        return Symbol()

    def get_offset(self, name):
        sym = self.get_sym(name)
        if sym is not None:
            return sym.st_value
        # print(f'WARNING: symbol {name} not found, returning invalid offset')
        return -1

    @classmethod
    def from_filename(cls, filename):
        return cls(open(filename, 'rb'))

    def read(self, size=-1):
        return self._fp.read(size)

    def seek(self, target, whence=os.SEEK_SET):
        return self._fp.seek(target, whence)
