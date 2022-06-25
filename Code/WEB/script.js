//déclarations des variables globales (utilisables dans plusieurs fonctions)
let mercury, mercuryRK, start, earth, sun, p1, p2, i = 0;


//fonction de récuperation du fichir JSON
async function demande(){
    //ouverture du JSON
    const reponse = await fetch('/mercury.json');
    const fichier = await reponse.json();

    //récupération de la liste voulue
    mercury = fichier['mercury-euler'];
    mercuryRK = fichier['mercury-RK'];

    //mise a l'échelle des coordonnées
    p1=echelle(mercury)
    p2=echelle(mercuryRK)
}


//fontion de mise a l'échelle qui retourne les coordonnées dans une variable globale pour etre utilisée dans d'autres focntions
function echelle(planete){
    let result=[];
    //la boucle rempli un nouveau tableau(result) avec les coordonnée mreduite a l'echelle de l'écran(par une regle de 3)
    for(element in planete){
        result[element] = [];
        result[element][0] = ((planete[element][0][0] * 800) / 8e+11) + (windowWidth/2)-15;
        result[element][1] = -((planete[element][0][1] * 800) / 8e+11) + (windowHeight/2)-15;
    };

    return result
}


//fonction qui initialise l'espace de travail dans la fenetre
async function setup(){
    createCanvas(windowWidth, windowHeight);
    start = false;
    await demande();
    start = true;

    // affichage du soleil
    sun = createImg(
        '/assets/soleil.png',
        'soleil'
    );
    sun.position(windowWidth/2-25, windowHeight/2-25);
    sun.size(25,25);
}   


//fonction qui affiche la trajectoire de la planète ainsi que la planète en orbite autour du soleil
function planete(data, i, couleur){
    
    //affichage de la trace
    stroke(couleur);
    noFill();
    beginShape();
    for(let k=0; k<data.length-1; k+=50)
    {
        curveVertex(data[k][0], data[k][1]);
    }
    endShape();

    //affichage de la planète en orbite
    stroke(couleur)
    strokeWeight(10)
    point(data[i][0], data[i][1])
    strokeWeight(1);
}


//fonction de la librairie P5.js qui boucle a l'infini et qui gère l'affichage des planetes en orbite 
function draw(){
    
    //condition pour eviter que la boucle ne commence avant que le fichier JSON soit ouvert correctement
    if(start)
    {
        //initialisation du fond 
        background(0);

        //affichage des planètes 
        planete(p1, i, '#0000FF');
        planete(p2, i, '#00FF00');

        //incrementation du i (pour l'affichage des palnetes en fonction du temps)
        i+=20;
        if(i>=36500)
        {
            i=0
        }
    }
}



