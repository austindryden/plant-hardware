const db = require('../backend/connection');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');
const port = new SerialPort('/dev/ttyACM0', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: "\n" }));
let dataArr = [];
let counter = 0;
// Read the port data

port.on("open", () => {
  console.log('serial port open');
});

parser.on('data', async data =>{
  console.log('got word from arduino:', data);
  counter +=1;
  dataArr.push(data);
  if (counter >= 12){
    counter = 0;  
  }
});