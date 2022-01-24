// Configure the viewer
const buttonPluginState = false;

const viewer = makeBIMDataViewer({
	logger: {
		level: "INFO"
	},

	ui: {
		style: {
			backgroundColor: "#FFFFFF",
		},
		headerVisible: false,
		windowManager: false,
		version: false,
		bimdataLogo: false, // https://developers.bimdata.io/viewer/reference/context_menu.html#default-commands
		contextMenu: false, // menù tasto dx per vedere comandi di default es. deseleziona o seleziona tutto
	},

	plugins: {
		// 3d 2d button plugin
		fullscreen: true,
		"window-split": true,

		// 2D Viewer as window plugin
		viewer2d: true,

		// 2D Viewer as button plugin
		"viewer2d-parameters": buttonPluginState,
		measure2d: buttonPluginState,
		"viewer2d-screenshot": buttonPluginState,

		// 3D Viewer as window plugin
		viewer3d: {
			pivotMarker: true, // puntino su 3d durante rotazione
			navCube: true, // cubo di orientazione edificio
			edges: true,
			enableOffsets: true,
		},

		// 3D Viewer as button plugin
		"viewer3d-parameters": buttonPluginState,
		"structure-properties": buttonPluginState,
		bcf: buttonPluginState,
		section: buttonPluginState,
		projection: buttonPluginState,
		search: buttonPluginState,

		// Spatial tree as window plugin
		structure: {
			merge: false,
			export: false,
		},

		// Properties as window plugin
		properties: {
			editProperties: false
		},

		// Window Selector as window plugin
		windowSelector: true,
	},
	api: {
		//ifcIds: [15097],
		cloudId: 10344,
		projectId: 237466,
		accessToken: "TAbdyPzoQeYgVSMe4GUKoCEfYctVhcwJ",
		//apiUrl: "",
	}

});


// MQTT
//var hostname = "broker.hivemq.com";
// var hostname = "fridaycloud.ddns.net";
// var port = 8001;
 var lastSubbed = ""
// mqttClient = new Paho.MQTT.Client(hostname, port, "bimdata mesh");
// mqttClient.onMessageArrived = MessageArrived;
// mqttClient.onConnectionLost = ConnectionLost;
// //Connect();
// /*Initiates a connection to the MQTT broker*/
// function Connect() {
// 	mqttClient.connect({
// 		onSuccess: Connected,
// 		onFailure: ConnectionFailed,
// 		keepAliveInterval: 10,
// 		useSSL: false,
// 	});
// }


function subscribeToUUID(uuid) {
	geoInit(uuid)
	if (lastSubbed != "") {

		unsubscribeToUUID(lastSubbed)
	}
	//mqttClient.subscribe("bimTest/" + uuid)
	lastSubbed = uuid
}

function unsubscribeToUUID(uuid) {
	geoDestroy();
	document.getElementById("ggbApplet").innerText =""
	//mqttClient.unsubscribe("bimTest/" + uuid)
}



// /*Callback for successful MQTT connection */
// function Connected() {
// 	console.log("Connected");
// }
// /*Callback for failed connection*/
// function ConnectionFailed(res) {
// 	console.log("Connect failed:" + res.errorMessage);
// }
// /*Callback for lost connection*/
// function ConnectionLost(res) {
// 	if (res.errorCode !== 0) {
// 		console.log("Connection lost:" + res.errorMessage);
// 		Connect();
// 	}
// }
// /*Callback for incoming message processing */
// function MessageArrived(message) {
// 	console.log(message.destinationName + " : " + message.payloadString);
// 	msg = JSON.parse(message.payloadString)
// 	//sensorName = msg["sensor"]
// 	//temperature = msg["x"]
// 	//document.getElementById("view_log").innerText = sensorName + " temperature: " + temperature + "°";
	
// 	x = msg["x"]
// 	y = msg["y"]
// 	document.getElementById("view_log").innerText = "[x,y]: " + "[" + x + "," + y + "]" ;
// }

// BIMDATA


const componentView = {
	name: "Component_View",
	template: `
				<div
				id="ggbApplet"
				style="height: 100%;
				display: flex;
				justify-content:center;
				align-items:center;"
				>
				
				<div>
			</div>`,
};

const pluginView = {
	name: "pluginView",
	component: componentView,
};

// plugin che gestisce la subscription al server MQTT in seguito alla selezione di un elemento nel viewer2d
const pluginSelect2d = {
	name: "pluginSelect2d",
	startupScript($viewer) {

		$viewer.state.hub.on("objects-selected", ({ objects }) => {


			message = $viewer.state.selectedObjects
			subscribeToUUID(message[0].uuid)

			//document.getElementById("view_log").innerText = message[0].longname


			if (message[0].hasOwnProperty("longname")) {
				console.log("\nSelected uuid: " + message[0].uuid);
			}
		});

		$viewer.state.hub.on("objects-deselected", ({ objects }) => {


			message = $viewer.state.deselectedObjects
			unsubscribeToUUID(lastSubbed)
			if (message[0].hasOwnProperty("longname")) {
				console.log("Deselected uuid: " + lastSubbed);
			}
			lastSubbed = ""

			//document.getElementById("view_log").innerText = "___"


		}

		);

	},

};



viewer.registerPlugin(pluginView);
viewer.registerPlugin({
	name: "selectionEnableDisablePlugin",
	component: {
		// inibizione della selezione e dell'evidenziazione dal viewer3d
		created() {
			const viewer3dPlugin = this.$viewer.localContext.getPlugin("viewer3d");
			viewer3dPlugin.selectOnClick = false
			viewer3dPlugin.highlightOnHover = false
		},
	},
	addToWindows: ["3d"] // <-- Here is the trick

});
viewer.registerPlugin(pluginSelect2d);


const view = {
	name: "view",
	plugins: ["pluginView"],
};

viewer.registerWindow(view);


// Mount custom layout
const customLayout = {
	ratios: [40, 60],
	children: [
		"2d",
		{
			ratios: [50, 50],
			direction: "column",
			children: ["3d", "view"],
		},
	],
};


viewer.mount("#viewerId", customLayout);
viewer.setLocale("en");
viewer.loadIfcs([15097]);

//viewer.setAccessToken("TAbdyPzoQeYgVSMe4GUKoCEfYctVhcwJ");