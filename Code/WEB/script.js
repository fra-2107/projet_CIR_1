let mercury

async function request(){
    const reponse = await fetch('/mercury.json');
    const fichier = await reponse.json();
    mercury = fichier['mercury-euler'];
}
async function setup(){
    createCanvas(windowWidth, windowHeight, WEBGL);
    background(0);
    let start = false;
    await request();
    start = true;
}

function preload(){

}

function draw(){
    if(start)
    {
        
    }
}

