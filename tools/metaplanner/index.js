const { app, BrowserWindow } = require('electron');

let windowList = [];

function createWindow() {
	let win = new BrowserWindow({ 
		width: 720, height: 480,
		webPreferences: {
			webSecurity: false,
			backgroundThrottling: false,
			nodeIntegration: true,
		},
		show: false,
	});
	win.once('ready-to-show', ()=>win.show());
	win.loadFile('index.html');
	win.on('closed', ()=> {
		windowList = windowList.filter(x=>x!=win);
	});
	win.on('unresponsive', ()=>win.reload());
	windowList.push(win);
	win.webContents.openDevTools();
	return win;
}

app.on('ready', createWindow);
app.on('window-all-closed', ()=>{
	app.quit();
});
