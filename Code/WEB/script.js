let mercury;
let start;
let earth;
let sun;
let p1;
let i = 0;

async function demande(){
    const reponse = await fetch('/mercury.json');
    const fichier = await reponse.json();
    mercury = fichier['mercury-RK'];
    p1=echelle(mercury)
}

function echelle(planete){
    let result=[];
    for(element in planete){
        result[element] = [];
        result[element][0] = ((planete[element][0][0] * 800) / 8e+11) + (windowWidth/2)-15;
        result[element][1] = -((planete[element][0][1] * 800) / 8e+11) + (windowHeight/2)-15;
    };

    return result
}

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

function planete(data, i){
    stroke('#0000FF');
    noFill();
    beginShape();
    for(let k=0; k<data.length-1; k+=20)
    {
        curveVertex(data[k][0], data[k][1]);
        // console.log(k)
    }
    endShape();

    stroke('white')
    strokeWeight(10)
    point(data[i][0], data[i][1])
    strokeWeight(1);
}

function draw(){
    if(start)
    {
        background(0);
        planete(p1, i);

        i++;
        if(i>=36500)
        {
            i=0
        }
        // for(element in p1){
        //     earth = createImg(
        //         '/assets/earth.png',
        //         'terre'
        //     );
        //     earth.position(p1[element][0][0], p1[element][0][1]);
        //     earth.size(50, 50);  
        //     // earth.remove();
        // };
        //affichage de la terre
        // earth = createImg(
        //     '/assets/earth.png',
        //     'terre'
        // );
        // earth.position(p1, 10);
        // earth.size(50, 50);  
        // // earth.remove();
    }
}



