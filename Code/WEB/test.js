//déclarations des variables globales (utilisables dans plusieurs fonctions)
let start, p1, p2, p3, p4, p5, p6, p7, p8, i;
let header = document.getElementById('titre');
let system = document.getElementById('system');
let projet = document.getElementById('projet');
let btn1 = document.getElementById('btn1');
let btn2 = document.getElementById('btn2');
let v = document.getElementById("vitesse");
let x ;

let fichiermercure, fichiervenus, fichierterre, fichiermars, fichierjupiter, fichiersaturne, fichieruranus, fichierneptune
let mercure, venus, terre, mars, jupiter, saturne, uranus, neptune


//fonction de récuperation du fichir JSON
async function demande(){

    //ouverture du JSON
    const reponsemercure = await fetch('../Data/Mercure-euler.json');
    fichiermercure = await reponsemercure.json();

    const reponsevenus = await fetch('../Data/Venus-euler.json');
    fichiervenus = await reponsevenus.json();

    const reponseterre = await fetch('../Data/Terre-euler.json');
    fichierterre = await reponseterre.json();

    const reponsemars = await fetch('../Data/Mars-euler.json');
    fichiermars = await reponsemars.json();

    const reponsejupiter = await fetch('../Data/Jupiter-euler.json');
    fichierjupiter = await reponsejupiter.json();

    const reponsesaturne = await fetch('../Data/Saturne-euler.json');
    fichiersaturne = await reponsesaturne.json();

    const reponseuranus = await fetch('../Data/Uranus-euler.json');
    fichieruranus = await reponseuranus.json();

    const reponseneptune = await fetch('../Data/Neptune-euler.json');
    fichierneptune = await reponseneptune.json();

    //récupération de la liste voulue
    euler();

    //mise a l'échelle des coordonnées
    p2=echelle(mercure)
    p3=echelle(venus)
    p4=echelle(terre)
    p5=echelle(mars)
    p6=echelle(jupiter)
    p7=echelle(saturne)
    p8=echelle(uranus)
    p9=echelle(neptune)
    
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
    mercure = fichiermercure['Mercure-euler'];
    venus = fichiervenus['Venus-euler'];
    terre = fichierterre['Terre-euler'];
    mars = fichiermars['Mars-euler'];
    jupiter = fichierjupiter['Jupiter-euler'];
    saturne = fichiersaturne['Saturne-euler'];
    uranus = fichieruranus['Uranus-euler'];
    neptune = fichierneptune['Neptune-euler'];
}

function setup(){
    btn2.className='off';
    v.className='off';
    document.getElementById("vit").value = 20;
    i=0;
}

//fonction qui initialise l'espace de travail dans la fenetre
async function initialisation(){
    btn2.className='bouton';
    v.className='vitesse';
    header.className='off';
    system.className='off';
    projet.className='off';
    btn1.className='off';

    //creation du canvas
    createCanvas(windowWidth, windowHeight, WEBGL);
    start = false;
    await demande();
    start = true;

    document.getElementById("vit").value=0;
}   

//fonction qui affiche la trajectoire de la planète ainsi que la planète en orbite autour du soleil
function planete(data, i, couleur){
    
    //affichage de la trace
    stroke(couleur);
    noFill();
    beginShape();
    for(let k=0; k<data.length-1; k+=50000)
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
        planete(p2, i, '#00FF00');
        planete(p3, i, '#B2A6A4');
        planete(p4, i, '#0000FF');
        planete(p5, i, '#E84F1A');
        planete(p6, i, '#EEAE5D');
        planete(p7, i, '#E5C193');
        planete(p8, i, '#B8C6EB');
        planete(p9, i, '#567EEE');

        //incrementation du i (pour l'affichage des palnetes en fonction du temps)
        i+=x;
        if(i>=1000000)
        {
            console.log("i="+i)
            console.log(typeof(i))
            i=0
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
    btn1.className="bouton";
    btn2.className='off';    
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