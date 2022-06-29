// preparation du model 
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

    //creation du canvas
    createCanvas(windowWidth, windowHeight, WEBGL);
    start = false;
    await demande();

    //test si fichier
    if (fichier==1)
    {
        start = true;
        document.getElementById("vit").value=0;
    }
    else 
    {
        alert('veuillez entrer un fichier');
        arret();
    } 
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

        //affichage du soleil
        stroke('red');
        strokeWeight(20);
        point(0,0,0);
        strokeWeight(1);

        //affichage des planètes 
        planete(p1, i, '#00FF00', 1010, 20);
        planete(p2, i, '#B2A6A4', 2600, 100);
        planete(p3, i, '#0000FF', 4500, 250);
        planete(p4, i, '#E84F1A', 9000, 800);
        planete(p5, i, '#EEAE5D', 60000, 5000);
        planete(p6, i, '#E5C193',150000,  10000);
        planete(p7, i, '#B8C6EB', 450000, 50000);
        planete(p8, i, '#567EEE', 599999, 50000);

        //incrementation du i (pour l'affichage des palnetes en fonction du temps)
        i+=x;
        if(i>=p8.length)
        {
            i=0;
        }
    }
}
