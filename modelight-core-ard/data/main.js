var gateway = `ws://${window.location.hostname}/ws`;

var websocket;

// listen for web page event
window.addEventListener('load', onLoad);

// initialize web socket on web page load
function onLoad(event) {
    initWebSocket();
}

// initialize web socket function
function initWebSocket() {
    console.log('Opening WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    // websocket.onmessage = onMessage;
}

// if a new client connects
function onOpen(event) {
    console.log('Connection opened');
}

// if a client disconnects
function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

// // process a newly received message
// function onMessage(event) {
//     // convert received data to JSON
//     console.log(event.data);
//     let message_object = JSON.parse(event.data);
//     let message_keys = Object.keys(message_object);

//     for (let i = 0; i < message_keys.length; i++){
//         let key = message_keys[i];

//         // get the LED IDs and set the current state value e.g key=>led1 : value=> 1
//         document.getElementById(key).innerHTML = message_object[key];
//     }

//     console.log(message_object);
// }


/*
    LED controls
 */

// LEVEL 1 ALL ON
function led1on() {
    websocket.send('led1on');
}

// led 1 off
function led1off(){
    websocket.send('led1off');
}

function led2on(){
    websocket.send('led2on');
}

// led 2 off
function led2off(){
    websocket.send('led2off');
}

function led3on(){
    websocket.send('led3on');
}

// led 1 off
function led3off(){
    websocket.send('led3off');
}

////////////////// LEVEL 1 ////////////////// 
// RED
function ledR1on() {
    websocket.send('ledR1on')
}

function ledR1off() {
    websocket.send('ledR1off')
}

// GREEN
function ledG1on() {
    websocket.send('ledG1on')
}

function ledG1off() {
    websocket.send('ledG1off')
}

// BLUE
function ledB1on() {
    websocket.send('ledB1on')
}

function ledB1off() {
    websocket.send('ledB1off')
}



////////////////// LEVEL 2 ////////////////// 
// RED
function ledR2on() {
    websocket.send('ledR2on')
}

function ledR2off() {
    websocket.send('ledR2off')
}

// GREEN
function ledG2on() {
    websocket.send('ledG2on')
}

function ledG2off() {
    websocket.send('ledG2off')
}

// BLUE
function ledB2on() {
    websocket.send('ledB2on')
}

function ledB2off() {
    websocket.send('ledB2off')
}

////////////////// LEVEL 3 ////////////////// 
// RED
function ledR3on() {
    websocket.send('ledR3on')
}

function ledR3off() {
    websocket.send('ledR3off')
}

// GREEN
function ledG3on() {
    websocket.send('ledG3on')
}

function ledG3off() {
    websocket.send('ledG3off')
}

// BLUE
function ledB3on() {
    websocket.send('ledB3on')
}

function ledB3off() {
    websocket.send('ledB3off')
}

