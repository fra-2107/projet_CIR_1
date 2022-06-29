//déclarations des variables globales (utilisables dans plusieurs fonctions)
let start, p1, p2, p3, p4, p5, p6, p7, p8, i, x, y=20, fichier = 0, mercure, venus, terre, terreas, terrerk, mars, jupiter, saturne, uranus, neptune, fichiereuler, fichiereulerasy, fichierrk, stringData='';
let header = document.getElementById('titre');
let system = document.getElementById('system');
let projet = document.getElementById('projet');
let btnstart = document.getElementById('btn1');
let btnstop = document.getElementById('btn2');
let v = document.getElementById("vitesse");
let select_fichier=document.getElementById("file");
var file, fichierSelectionne;

//fonction de recuperation du fichier soumis par l'utilisateur 
function changeHandler(evt) {
    evt.stopPropagation();
    evt.preventDefault();
    fichier=1;

    //recuperation des information sur le fichier
    var files = evt.target.files;
    file = files[0];    
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

    return result;
}

//recuperation des coordonées par la methode euler
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

//recuperation des coordonées par la methode euler asymetrique
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

//recuperation des coordonées par la methode Runge kutta
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

//fonction desactivant le canvas et donc le model
function arret(){
    i=0;
    start=0;
    noCanvas();
    header.className='titre';
    system.className='system';
    projet.className='projet';
    btnstart.className="bouton";
    select_fichier.className='file';
    btnstop.className='off';    
    v.className='off';
}

//fonction qui affiche la trajectoire de la planète ainsi que la planète en orbite autour du soleil
function planete(data, i, couleur, longueur, resolution){
    
    //affichage de la trace
    stroke(couleur);
    noFill();
    beginShape();
    for(let k=0; k<longueur; k+=resolution)
    {
        curveVertex(data[k][0], data[k][1], data[k][2]);
    }
    endShape();

    //affichage de la planète en orbite
    stroke(couleur);
    strokeWeight(10);
    point(data[i][0], data[i][1], data[i][2]);
    strokeWeight(1);
}

//fonction permettant la pause du mouvement de l'orbite 
function arret_orbite(){
    y=document.getElementById("vit").value;
    document.getElementById("vit").value = "0";
    vit.className='off';
}

//fonction permettant de reprendre le mouvement de l'orbite 
function play_orbite(){
    document.getElementById("vit").value = y;
    vit.className='vit';
}

//fonction de récuperation du fichir JSON nessecaire
async function demande(){
    if (fichier==1)
    {
        if (file.name=="Euler.json")
        {
            const reponseeuler = await fetch('../../Code/Data/Euler.json');
            fichiereuler=await reponseeuler.json();

            euler();
        }
        if(file.name=="EulerAsy.json")
        {
            const reponseeulerasy = await fetch('../../Code/Data/EulerAsy.json');
            fichiereulerasy=await reponseeulerasy.json();

            eulerAsy();
        }
        if(file.name=="RK2.json")
        {
            const reponserk = await fetch('../../Code/Data/RK2.json');
            fichierrk=await reponserk.json();

            RK2();
        }

        //mise à echelle des planètes 
        p1=echelle(mercure);
        p2=echelle(venus);
        p3=echelle(terre);
        p4=echelle(mars);
        p5=echelle(jupiter);
        p6=echelle(saturne);
        p7=echelle(uranus);
        p8=echelle(neptune);
    }
}