var applet;
var subscription = "test";

var n2x = 0.2
var n2y = 0.2
var n1x = 1.6
var n1y = 0.2
var n0x = 1.4
var n0y = 1.4

var hostname = "fridaycloud.ddns.net";
var port = 8001;

mqttClient = new Paho.MQTT.Client(hostname, port,"zeruel");
mqttClient.onMessageArrived = MessageArrived;
mqttClient.onConnectionLost = ConnectionLost;

function Connect(){
    mqttClient.connect({
        onSuccess: Connected,
        onFailure: ConnectionFailed,
        keepAliveInterval: 10,
        useSSL: false,});
}
/*Callback for successful MQTT connection */
function Connected() {
    console.log("Connected: "+subscription);
    mqttClient.subscribe("bimTest/"+subscription);
}
/*Callback for failed connection*/
function ConnectionFailed(res) {
    console.log("Connect failed:" + res.errorMessage);
}
/*Callback for lost connection*/
function ConnectionLost(res) {
    if (res.errorCode !== 0) {
        console.log("Connection lost:" + res.errorMessage);
        Connect();
    }
}
/*Callback for incoming message processing */
function MessageArrived(message) {
  msg = JSON.parse(message.payloadString);
  var x = msg["x"]
  var y = msg["y"]
  var r0 = msg["r0"]
  var r1 = msg["r1"]
  var r2 = msg["r2"]
    applet.evalCommand("B = ("+x+","+y+")")
    applet.evalCommand("SetColor(B,\"orange\")")

    applet.evalCommand("a = Circle(NODO2,B)")
    applet.evalCommand("SetColor(a,0,255,0)")

applet.evalCommand("b = Circle(NODO1,B)")
applet.evalCommand("SetColor(b,255,0,0)")
applet.evalCommand("c = Circle(NODO0,B)")
applet.evalCommand("SetColor(c,0,0,255)")

applet.evalCommand("l = Segment(NODO2,B)")
applet.evalCommand("SetColor(l,0,255,0)")

applet.evalCommand("m = Segment(NODO1,B)")
applet.evalCommand("SetColor(m,255,0,0)")

applet.evalCommand("n = Segment(NODO0,B)")
applet.evalCommand("SetColor(n,0,0,255)")

applet.evalCommand("werr = Slider(0,5,0.1)")

applet.evalCommand("eq1: (x-"+n0x+")^(2)+(y-"+n0y+")^(2)≤("+r0+"-werr)^(2) ∧ (x-"+n1x+")^(2)+(y-"+n1y+")^(2)≤("+r1+"-werr)^(2) ∧ (x-"+n2x+")^(2)+(y-"+n2y+")^(2)≤("+r2+"-werr)^(2) ∨ (x-"+n0x+")^(2)+(y-"+n0y+")^(2)≤("+r0+"+werr)^(2) ∧ (x-"+n1x+")^(2)+(y-"+n1y+")^(2)≤("+r1+"+werr)^(2) ∧ (x-"+n2x+")^(2)+(y-"+n2y+")^(2)≤("+r2+"+werr)^(2)")

}

async function drawPoints(applet){
  this.applet = applet;
  applet.evalCommand("SetPerspective(\"G\")")
    applet.setMode(40)

applet.evalCommand("ZoomIn(0.4,(0,-8))")
//applet.evalCommand("ZoomIn(-10,-10,20,20)")

applet.evalCommand("X = (3.75,3.68)")
applet.evalCommand("SetVisibleInView(X,1,false)")
applet.evalCommand("Y = (-3.3,3.68)")
applet.evalCommand("SetVisibleInView(Y,1,false)")
applet.evalCommand("W = (-3.3,-3.25)")
applet.evalCommand("SetVisibleInView(W,1,false)")
applet.evalCommand("Z = (3.75,-3.25)")
applet.evalCommand("SetVisibleInView(Z,1,false)")
applet.evalCommand("room = Polygon(X,Y,W,Z)")
applet.evalCommand("SetColor(room,\"cyan\")")


applet.evalCommand("NODO2 = ("+n2x+","+n2y+")")
applet.evalCommand("SetColor(NODO2,0,255,0)")
applet.evalCommand("NODO1 = ("+n1x+","+n1y+")")
applet.evalCommand("SetColor(NODO1,255,0,0)")
applet.evalCommand("NODO0 = ("+n0x+","+n0y+")")
applet.evalCommand("SetColor(NODO0,0,0,255)")

applet.evalCommand("R = (0,0)")
applet.evalCommand("SetVisibleInView(R,1,false)")
applet.evalCommand("S = (1.8,0)")
applet.evalCommand("SetVisibleInView(S,1,false)")
applet.evalCommand("T = (1.8,1.6)")
applet.evalCommand("SetVisibleInView(T,1,false)")
applet.evalCommand("U = (0,1.6)")
applet.evalCommand("SetVisibleInView(U,1,false)")
applet.evalCommand("table = Polygon(R,S,T,U)")
applet.evalCommand("SetColor(table,\"brown\")")
}

function geoDestroy(){
    mqttClient.disconnect();
    applet = null
}

function geoInit(sub){
    subscription = sub
    Connect()
var parameters = {
"id": "ggbApplet",
"width":document.getElementById("ggbApplet").clientWidth,
"height":document.getElementById("ggbApplet").clientHeight,
"showMenuBar":false,
"showAlgebraInput":false,
"showAlgebraView":false,
"showToolBar":false,
"customToolBar":"0 73 62 | 1 501 67 , 5 19 , 72 75 76 | 2 15 45 , 18 65 , 7 37 | 4 3 8 9 , 13 44 , 58 , 47 | 16 51 64 , 70 | 10 34 53 11 , 24  20 22 , 21 23 | 55 56 57 , 12 | 36 46 , 38 49  50 , 71  14  68 | 30 29 54 32 31 33 | 25 17 26 60 52 61 | 40 41 42 , 27 28 35 , 6",
"showToolBarHelp":false,
"showResetIcon":false,
"enableLabelDrags":false,
"enableShiftDragZoom":true,
"enableRightClick":false,
"errorDialogsActive":false,
"useBrowserForJS":false,
"allowStyleBar":false,
"preventFocus":false,
"showZoomButtons":true,
"capturingThreshold":3,
// add code here to run when the applet starts
"appletOnLoad":function(api){ /* api.evalCommand('Segment((1,2),(3,4))');*/ drawPoints(api)},
"showFullscreenButton":true,
"scale":1,
"disableAutoScale":false,
"allowUpscale":false,
"clickToLoad":false,
"appName":"classic",
"buttonRounding":0.7,
"buttonShadows":false,
"language":"it",
// use this instead of ggbBase64 to load a material from geogebra.org
// "material_id":"RHYH3UQ8",
// use this instead of ggbBase64 to load a .ggb file
// "filename":"myfile.ggb",
"ggbBase64":"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",
};
// is3D=is 3D applet using 3D view, AV=Algebra View, SV=Spreadsheet View, CV=CAS View, EV2=Graphics View 2, CP=Construction Protocol, PC=Probability Calculator DA=Data Analysis, FI=Function Inspector, macro=Macros
var views = {'is3D': 0,'AV': 1,'SV': 0,'CV': 0,'EV2': 0,'CP': 0,'PC': 0,'DA': 0,'FI': 0,'macro': 0};
var applet = new GGBApplet(parameters, '5.0', views);
//window.onload = function() {applet.inject('ggbApplet')};
applet.inject('ggbApplet')
applet.setPreviewImage('data:image/gif;base64,R0lGODlhAQABAAAAADs=','https://www.geogebra.org/images/GeoGebra_loading.png','https://www.geogebra.org/images/applet_play.png');

}
