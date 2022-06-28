//déclarations des variables globales (utilisables dans plusieurs fonctions)
let start, commencer, p1, p2, p3, p4, p5, p6, p7, p8, i;
let header = document.getElementById('titre');
let system = document.getElementById('system');
let projet = document.getElementById('projet');
let btnstart = document.getElementById('btn1');
let btnstop = document.getElementById('btn2');
let btndemo = document.getElementById('btn5');
let v = document.getElementById("vitesse");
let x ;
var file
let fichier = 0

let fichiermercure, fichiervenus, fichierterre, fichiermars, fichierjupiter, fichiersaturne, fichieruranus, fichierneptune
let mercure, venus, terre, terreas, terrerk, mars, jupiter, saturne, uranus, neptune
var fichierSelectionne

let fichiereuler, fichiereulerasy, fichierrk
let stringData=''

function changeHandler(evt) {
    evt.stopPropagation();
    evt.preventDefault();
    fichier=1
    // FileList object.
    var files = evt.target.files;

    file = files[0];

    var fileReader = new FileReader();


    fileReader.onload = function(progressEvent) {
        stringData = fileReader.result;
    
        fichierSelectionne = JSON.parse(stringData)
    }

    // Read file asynchronously.
    fileReader.readAsText(file, "UTF-8"); // fileReader.result -> String.
    
}


//fonction de récuperation du fichir JSON
async function demande(){
    
    const reponseeuler = await fetch('../Data/Euler.json')
    fichiereuler=await reponseeuler.json();

    const reponseeulerasy = await fetch('../Data/EulerAsy.json')
    fichiereulerasy=await reponseeulerasy.json();

    const reponserk = await fetch('../Data/RK2.json')
    fichierrk=await reponserk.json();
}


//fontion de mise a l'échelle qui retourne les coordonnées dans une variable globale pour etre utilisée dans d'autres focntions
function echelle(planete){
    let result=[];
    //la boucle rempli un nouveau tableau(result) avec les coordonnée mreduite a l'echelle de l'écran(par une regle de 3)
    for(element in planete){
        result[element] = [];
        result[element][0] = ((planete[element][0][0] * 800) / 8e+11);
        result[element][1] = -((planete[element][0][1] * 800) / 8e+11);
    };

    return result
}

function euler(){
    mercure = fichiereuler['Mercure-Euler'];
    venus = fichiereuler['Venus-Euler'];
    terre = fichiereuler['Terre-Euler'];
    mars = fichiereuler['Mars-Euler'];
    jupiter = fichiereuler['Jupiter-Euler'];
    saturne = fichiereuler['Saturne-Euler'];
    uranus = fichiereuler['Uranus-Euler'];
    neptune = fichiereuler['Neptune-Euler'];
}

function eulerAsy(){
    mercure = fichiereulerasy['Mercure-EulerAsy'];
    venus = fichiereulerasy['Venus-EulerAsy'];
    terre = fichiereulerasy['Terre-EulerAsy'];
    mars = fichiereulerasy['Mars-EulerAsy'];
    jupiter = fichiereulerasy['Jupiter-EulerAsy'];
    saturne = fichiereulerasy['Saturne-EulerAsy'];
    uranus = fichiereulerasy['Uranus-EulerAsy'];
    neptune = fichiereulerasy['Neptune-EulerAsy'];
}

function RK2(){
    mercure = fichierrk['Mercure-RK2'];
    venus = fichierrk['Venus-RK2'];
    terre = fichierrk['Terre-RK2'];
    mars = fichierrk['Mars-RK2'];
    jupiter = fichierrk['Jupiter-RK2'];
    saturne = fichierrk['Saturne-RK2'];
    uranus = fichierrk['Uranus-RK2'];
    neptune = fichierrk['Neptune-RK2'];
}

function setup(){
    btnstop.className='off';
    v.className='off';
    document.getElementById("vit").value = 20;
    i=0;
}

//fonction qui initialise l'espace de travail dans la fenetre
async function initialisation(){
    btnstop.className='bouton';
    v.className='vitesse';
    header.className='off';
    system.className='off';
    projet.className='off';
    btnstart.className='off';
    btndemo.className='off';


    //creation du canvas
    createCanvas(windowWidth, windowHeight, WEBGL);
    start = false;
    // console.log(file.name)
    await demande();
    if (fichier==1)
    {
        if (file.name=="Euler.json")
        {
            euler();
        }
        if(file.name=="EulerAsy.json")
        {
            eulerAsy();
        }
        if(file.name=="RK2.json")
        {
            RK2();
        }
    }
    else 
    {
        alert('veuillez entrer un fichier')
    }

    p1=echelle(mercure)
    p2=echelle(venus)
    p3=echelle(terre)
    p4=echelle(mars)
    p5=echelle(jupiter)
    p6=echelle(saturne)
    p7=echelle(uranus)
    p8=echelle(neptune)
    start = true;

    document.getElementById("vit").value=0;
}   

//fonction qui affiche la trajectoire de la planète ainsi que la planète en orbite autour du soleil
function planete(data, i, couleur){
    
    //affichage de la trace
    stroke(couleur);
    noFill();
    beginShape();
    for(let k=0; k<data.length-1; k+=500)
    {
        curveVertex(data[k][0], data[k][1], data[k][2]);
    }
    endShape();

    //affichage de la planète en orbite
    stroke(couleur)
    strokeWeight(10)
    point(data[i][0], data[i][1], data[i][2])
    strokeWeight(1);
}

//fonction de la librairie P5.js qui boucle a l'infini et qui gère l'affichage des planetes en orbite 
function draw(){
    
    //condition pour eviter que la boucle ne commence avant que le fichier JSON soit ouvert correctement
    if(start)
    {
        orbitControl();
        x = document.getElementById("vit").value;
        x=parseInt(x, 10);

        //initialisation du fond 
        background(0);
        stroke('red');
        strokeWeight(20);
        point(0,0,0);
        strokeWeight(1);

        //affichage des planètes 
        planete(p1, i, '#00FF00');
        planete(p2, i, '#B2A6A4');
        planete(p3, i, '#0000FF');
        planete(p4, i, '#E84F1A');
        planete(p5, i, '#EEAE5D');
        planete(p6, i, '#E5C193');
        planete(p7, i, '#B8C6EB');
        planete(p8, i, '#567EEE');

        //incrementation du i (pour l'affichage des palnetes en fonction du temps)
        i+=x;
        if(i>=p1.length)
        {
            i=0;
        }
    }
    else if(commencer)
    {
        orbitControl();
        x = document.getElementById("vit").value;
        x=parseInt(x, 10);

        //initialisation du fond 
        background(0);
        stroke('red');
        strokeWeight(20);
        point(0,0,0);
        strokeWeight(1);

        //affichage des planètes 
        planete(p1, i, '#00FF00');
        planete(p2, i, '#0000FF');
        planete(p3, i, '#FF00FF');

        //incrementation du i (pour l'affichage des palnetes en fonction du temps)
        i+=x;
        if(i>=p1.length)
        {
            i=0;
        }
    }
}

function arret(){
    i=0;
    start=0;
    noCanvas();
    header.className='titre';
    system.className='system';
    projet.className='projet';
    btnstart.className="bouton";
    btndemo.className="bouton";
    btnstop.className='off';    
    v.className='off';
}

function arret_orbite(){
    x=0;
    document.getElementById("vit").value = "0";
    vit.className='off'
}

function play_orbite(){
    x=1;
    document.getElementById("vit").value = "1";
    vit.className='vit'
}



async function demo(){
    const reponseterre = await fetch('../Data/Terre.json');
    fichierterre = await reponseterre.json();

    terre = fichierterre['Terre-euler'];
    terreas = fichierterre['Terre-eulerAsy'];
    terrerk = fichierterre['Terre-RK2'];

    p1=echelle(terre);
    p2=echelle(terreas);
    p3=echelle(terrerk);

}

async function init_demo(){
    btnstop.className='bouton';
    v.className='vitesse';
    header.className='off';
    system.className='off';
    projet.className='off';
    btnstart.className='off';
    btndemo.className='off';

    //creation du canvas
    createCanvas(windowWidth, windowHeight, WEBGL);
    commencer = false;
    await demo();
    commencer = true;

    document.getElementById("vit").value=0;
} 