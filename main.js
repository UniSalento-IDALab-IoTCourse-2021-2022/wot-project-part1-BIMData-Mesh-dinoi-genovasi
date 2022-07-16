//get Token
var accessToken = "eyJhbGciOiJSUzI1NiIsInR5cCIgOiAiSldUIiwia2lkIiA6ICI1Ql9OOGk4MnlCUWZkZnVfenByMGIyQ1Rfc21jV21kZDkzSTFQRGJXTkIwIn0.eyJleHAiOjE2NDkzMjc3ODMsImlhdCI6MTY0OTMyNDE4MywianRpIjoiMTExM2RiNzgtOWY4NS00NGJhLThjMTctMDdiZDI0NjM3NDUyIiwiaXNzIjoiaHR0cHM6Ly9pYW0uYmltZGF0YS5pby9hdXRoL3JlYWxtcy9iaW1kYXRhIiwiYXVkIjoiYWNjb3VudCIsInN1YiI6IjhkYTFhYzUwLWIxOTMtNDdlMC1iOWQ5LWFmYmMzMTgxYjEzYiIsInR5cCI6IkJlYXJlciIsImF6cCI6IjFhNDM5ZGE4LTk2MDAtNGUxYi05MTkwLWFiYTIzZmYwODk4OCIsImFjciI6IjEiLCJhbGxvd2VkLW9yaWdpbnMiOlsiaHR0cHM6Ly9hcGkuYmltZGF0YS5pbyJdLCJyZWFsbV9hY2Nlc3MiOnsicm9sZXMiOlsib2ZmbGluZV9hY2Nlc3MiLCJkZWZhdWx0LXJvbGVzLWJpbWRhdGEiLCJ1bWFfYXV0aG9yaXphdGlvbiJdfSwicmVzb3VyY2VfYWNjZXNzIjp7ImFjY291bnQiOnsicm9sZXMiOlsibWFuYWdlLWFjY291bnQiLCJtYW5hZ2UtYWNjb3VudC1saW5rcyIsInZpZXctcHJvZmlsZSJdfX0sInNjb3BlIjoiY2hlY2s6cmVhZCBtb2RlbDp0b2tlbl9tYW5hZ2Ugd2ViaG9vazptYW5hZ2UgZG9jdW1lbnQ6cmVhZCBjbG91ZDptYW5hZ2UgYmNmOndyaXRlIHVzZXI6cmVhZCBkb2N1bWVudDp3cml0ZSBvcmc6bWFuYWdlIHByb2ZpbGUgbW9kZWw6cmVhZCBlbWFpbCBiY2Y6cmVhZCBjaGVjazp3cml0ZSBtb2RlbDp3cml0ZSBjbG91ZDpyZWFkIiwiY2xpZW50SWQiOiIxYTQzOWRhOC05NjAwLTRlMWItOTE5MC1hYmEyM2ZmMDg5ODgiLCJlbWFpbF92ZXJpZmllZCI6ZmFsc2UsImNsaWVudEhvc3QiOiIyMTIuMTg5LjE0MC4xMyIsInByZWZlcnJlZF91c2VybmFtZSI6InNlcnZpY2UtYWNjb3VudC0xYTQzOWRhOC05NjAwLTRlMWItOTE5MC1hYmEyM2ZmMDg5ODgiLCJjbGllbnRBZGRyZXNzIjoiMjEyLjE4OS4xNDAuMTMifQ.XMirT7nxwWxZ9FCrEwGdX287M1K0wfYNizNjyeA4v0hliw9U953DH8axxMlesn364i8Q7wCKBUBE6-h-Z9XaqWP4WU33NgBcfe0eOW9e4gqtfXaBSkztqQWDtQPWREm50wc1EHStpj0oErXvcoQep2-1bGct_ZC1zvoYg_zEZwrH8UOPaTp302icGDulxH5KrCJUWbzoIZ6-OUGX3PNoxsKPAUqDHBb-zXOnSiH5eL8aMLv_AJuVLH_0QCKPsVAl2mSwsX_Z-Bq1ybc9bc5aBUy7Sdq6_wE0oMgUlFIsCpQTOShO31Kidp9RVOFF-MVwj044jC208TsZFXBIts4nNg";
// Configure the customViewer
const buttonPluginState = false;
// test
const customViewer = makeBIMDataViewer({
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
        bimdataLogo: false, // https://developers.bimdata.io/customViewer/reference/context_menu.html#default-commands
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
        cloudId: 15505,
        projectId: 345659,
        accessToken: accessToken
    }
});

var uuidSelectedElement = ""

function geogebraWindowCreate(uuid) {
    geoInit(uuid)
    if (uuidSelectedElement != "") {

        geogebraWindowDestroy(uuidSelectedElement)
    }
    uuidSelectedElement = uuid
}

function geogebraWindowDestroy(uuid) {
    geoDestroy();
    document.getElementById("ggbApplet").innerText =""
}

// BIMDATA

const geogebraComponent = {
    name: "geogebraComponent",
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

const geogebraPlugin = {
    name: "geogebraPlugin",
    component: geogebraComponent,
};

// plugin che gestisce la subscription al server MQTT in seguito alla selezione di un elemento nel viewer2d
const position2dPlugin = {
    name: "position2dPlugin",
    startupScript($customViewer) {
        $customViewer.state.hub.on("objects-selected", ({ objects }) => {
            message = $customViewer.state.selectedObjects
            geogebraWindowCreate(message[0].uuid)
            if (message[0].hasOwnProperty("longname")) {
                console.log("\nSelected uuid: " + message[0].uuid);
            }
        });
        $customViewer.state.hub.on("objects-deselected", ({ objects }) => {
            message = $customViewer.state.deselectedObjects
            geogebraWindowDestroy(uuidSelectedElement)
            if (message[0].hasOwnProperty("longname")) {
                console.log("Deselected uuid: " + uuidSelectedElement);
            }
            uuidSelectedElement = ""
        });
    },
};

customViewer.registerPlugin(geogebraPlugin);
customViewer.registerPlugin({
    name: "selectionEnableDisablePlugin",
    component: {
        // inibizione della selezione e dell'evidenziazione dal viewer3d
        created() {
            const viewer3dPlugin = this.$customViewer.localContext.getPlugin("viewer3d");
            viewer3dPlugin.selectOnClick = false
            viewer3dPlugin.highlightOnHover = false
        },
    },
    addToWindows: ["3d"] // <-- Here is the trick

});
customViewer.registerPlugin(position2dPlugin);

const geogebraWindow = {
    name: "geogebraWindow",
    plugins: ["geogebraPlugin"],
};

customViewer.registerWindow(geogebraWindow);

// Mount custom layout
const geogebraLayout = {
    ratios: [40, 60],
    children: [
        "2d",
        {
            ratios: [50, 50],
            direction: "column",
            children: ["3d", "geogebraWindow"],
        },
    ],
};

customViewer.mount("#viewerId", geogebraLayout);
customViewer.setLocale("en");
customViewer.loadIfcs([28999]);
