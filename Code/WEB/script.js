let mercury
let start
let earth
let sun


async function request(){
    const reponse = await fetch('/mercury.json');
    const fichier = await reponse.json();
    mercury = fichier['mercury-euler'];
}
async function setup(){
    createCanvas(windowWidth, windowHeight);
    background(0);
    start = false;
    await request();
    start = true;
    // affichage du soleil
    sun = createImg(
        '/assets/soleil.png'
    );
    sun.position(700, 300);
    sun.size(75,75);
}

function preload(){

}

function draw(){
    if(start)
    {
        //affichage de la terre
        earth = createImg(
            '/assets/earth.png'
        );
        earth.position(300, 10);
        earth.size(50, 50);  
    }
}

function mouseClicked() {
    earth.remove();
}
