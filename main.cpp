/*
    Yusuf Alparslan Kaya
    190202102
*/

#include <stdio.h>
#include <graphics.h>
#include <math.h>


//Yaricapimizda kullanmak icin sonsuz deger atamasi
float INF = 1e18;

struct Point{
    float x,y;
};

struct Circle{
    Point C;
    float r;
};

Circle MEC = { {0,0}, INF };
int noktaSayisi;



//Kordinat Duzlemimiz Her Nokta Arasý 20px Bosluk vardir.
void kordinatDuzlemi(){
    line(0,400,800,400);
    line(400,0,400,800);
    //X ekseni
    outtextxy(401,401,"0");
    outtextxy(420,401,"1");
    outtextxy(440,401,"2");
    outtextxy(460,401,"3");
    outtextxy(480,401,"4");
    outtextxy(500,401,"5");
    outtextxy(520,401,"6");
    outtextxy(540,401,"7");
    outtextxy(560,401,"8");
    outtextxy(580,401,"9");
    outtextxy(600,401,"10");
    outtextxy(620,401,"11");
    outtextxy(640,401,"12");
    outtextxy(660,401,"13");
    outtextxy(680,401,"14");
    outtextxy(700,401,"15");
    outtextxy(720,401,"16");
    outtextxy(740,401,"17");
    outtextxy(760,401,"18");
    outtextxy(380,401,"-1");
    outtextxy(360,401,"-2");
    outtextxy(340,401,"-3");
    outtextxy(320,401,"-4");
    outtextxy(300,401,"-5");
    outtextxy(280,401,"-6");
    outtextxy(260,401,"-7");
    outtextxy(240,401,"-8");
    outtextxy(220,401,"-9");
    outtextxy(200,401,"-10");
    outtextxy(180,401,"-11");
    outtextxy(160,401,"-12");
    outtextxy(140,401,"-13");
    outtextxy(120,401,"-14");
    outtextxy(100,401,"-15");
    outtextxy(80,401,"-16");
    outtextxy(60,401,"-17");
    outtextxy(40,401,"-18");
    //Y ekseni
    outtextxy(385,420,"-1");
    outtextxy(385,440,"-2");
    outtextxy(385,460,"-3");
    outtextxy(385,480,"-4");
    outtextxy(385,500,"-5");
    outtextxy(385,520,"-6");
    outtextxy(385,540,"-7");
    outtextxy(385,560,"-8");
    outtextxy(385,580,"-9");
    outtextxy(380,600,"-10");
    outtextxy(380,620,"-11");
    outtextxy(380,640,"-12");
    outtextxy(380,660,"-13");
    outtextxy(380,680,"-14");
    outtextxy(380,700,"-15");
    outtextxy(380,720,"-16");
    outtextxy(380,740,"-17");
    outtextxy(380,760,"-18");
    outtextxy(385,380,"1");
    outtextxy(385,360,"2");
    outtextxy(385,340,"3");
    outtextxy(385,320,"4");
    outtextxy(385,300,"5");
    outtextxy(385,280,"6");
    outtextxy(385,260,"7");
    outtextxy(385,240,"8");
    outtextxy(385,220,"9");
    outtextxy(380,200,"10");
    outtextxy(380,180,"11");
    outtextxy(380,160,"12");
    outtextxy(380,140,"13");
    outtextxy(380,120,"14");
    outtextxy(380,100,"15");
    outtextxy(380,80,"16");
    outtextxy(380,60,"17");
    outtextxy(380,40,"18");
}

//Noktalarimi yazdiralim
void yazdirNokta(struct Point points[], int numberOfPoints)
{
     for(int i = 0; i < numberOfPoints ; i++)
    {
        outtextxy(400+20*points[i].x, 400-20*points[i].y, "O");
    }
}

//Iki nokta arasindaki uzaklik
float distance(struct Point A, struct Point B)
{
    float dist = sqrt(pow( A.x - B.x ,2)+pow( A.y - B.y  ,2));
    return dist;
}

//Nokta cemberin içinde mi deðil mi?
int pointInside(struct Circle C, struct Point P)
{
    if(distance(C.C, P) <= C.r )
    {
        return 1;
    }else{
        return 0;
    }
}

//Verilen 2 nokta için çizilen çember
Circle twoPointsCircle(struct Point A, struct Point B)
{
    Point C = { (A.x + B.x) / 2.0, (A.y + B.y) / 2.0 };
    return {C, distance(A, B)/2};
};

//Verilen 3 nokta için çizilen çemberin merkez noktasý
Point threePointsCircleCenter(float bx, float by, float cx, float cy)
{
    float B = bx * bx + by * by;
    float C = cx * cx + cy * cy;
    float D = bx*cy - by*cx;
    return { (cy * B - by * C)/(2 * D), (bx * C - cx * B)/(2 * D) };
}

//Verilen 3 nokta için çizilen çemberin merkez ve yarýcap
Circle threePointsCircle(struct Point A, struct Point B, struct Point C)
{
    Point I = threePointsCircleCenter(B.x - A.x, B.y - A.y, C.x - A.x, C.y - A.y);
    I.x += A.x;
    I.y += A.y;
    return { I, distance(I, A) };
}

//Çemberimiz verilen tüm noktalarý kapsýyor mu?
int circleWithAllPoints(struct Circle C, struct Point points[], int numberOfPoints )
{
    int k = 0;
    for(int i = 0 ; i < numberOfPoints ; i++)
    {
        if(pointInside(C, points[i]))
        {
            k++;
        }
    }
    if(k == numberOfPoints)
    {
        return 1;
    }else{
        return 0;
    }
}

//Hangi cemberimiz daha kucuk kontrol!
Circle minimumEnclosingCircle(struct Point points[] ,int numberOfPoints)
{
    //Cemberimizi 0,0 noktasýndan sonsuz yaricaplý olarak olusturuyoruz.
    Circle MEC = { {0,0}, INF };

    //Butun ikili noktalarýmýza bakýyoruz ve en kucuk yarýcapli tum noktalarý kapsayan cemberimizi olusturuyoruz.
    for(int i = 0 ; i < numberOfPoints ; i++)
    {
        for(int k = i + 1 ; k < numberOfPoints ; k++)
        {
            Circle smallRadiusCircle = twoPointsCircle(points[i], points[k]);
            //Olusturulan cemberler daha kucuk yaricapa sahipse VE tum noktalarý kapsiyorsa yeni cemberimiz yapariz.
            if(smallRadiusCircle.r < MEC.r && circleWithAllPoints(smallRadiusCircle, points, numberOfPoints))
            {
                MEC = smallRadiusCircle;
            }
        }
    }

    //Uc noktaya birden bakýyoruz, yaricapimiz daha kucuk cikarsa ve tum noktalarimizi kapsiyorsa yeni cemberimiz.
    for(int i = 0 ; i < numberOfPoints ; i++)
    {
        for(int j = i + 1 ; j < numberOfPoints ; j++)
        {
            for(int k = j + 1 ; k < numberOfPoints ; k++)
            {
                Circle smallRadiusCircle = threePointsCircle(points[i], points[j], points[k]);
                //Olusturulan cemberler daha kucuk yaricapa sahipse VE tum noktalarý kapsiyorsa yeni cemberimiz yapariz.
                if(smallRadiusCircle.r < MEC.r && circleWithAllPoints(smallRadiusCircle, points, numberOfPoints))
                {
                    MEC = smallRadiusCircle;
                }
            }
        }
    }
    return MEC;
}

//***********************************************************************************************************************************
// Butun 3 lu kombinasyonlarý tek tek deneyip en kucuk cemberi elde etmek
void combination(struct Point points[], struct Point data[], int start, int end,
                     int index, int r);


void doCombination(struct Point points[], int n, int r)
{
    //Butun kombinasyonlarý tutmak icin gecici dizi
    struct Point data[r];
    combination(points, data, 0, n-1, 0, r);
}

/* points[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Starting and Ending indexes in points[]
   index  ---> Current index in data[]
   r ---> kombinasyon buyuklugu */
void combination(struct Point points[], struct Point data[], int start, int end, int index, int r)
{
    if (index == r)
    {
        //Butun olasý 3 nokta kombinasyonlarýný deneyip en kucuk cember merkezý ve yarýcapý belirleme
        Circle multiplePoints = minimumEnclosingCircle(data, r);
        for (int j=0; j<r; j++)
        {
            if(multiplePoints.r < MEC.r && circleWithAllPoints(multiplePoints, points, noktaSayisi))
            {
                MEC = multiplePoints;
            }
        }
        return;
    }
    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = points[i];
        combination(points, data, i+1, end, index+1, r);
    }
}
//****************************************************************************************************************************************/

//faktoriyel alma fonks.
int fact(int n)
{
    if(n==0)
        return 1;
    else
        return n*fact(n-1);
}

//kombinasyon fonks.
int comb(int n, int r)
{
    return (fact(n)/(fact(n-r)*fact(r)));
}

//bezier curve fonks.
void spline(struct Point points[], int numberOfPoints)
{
    float t,x,y;
    int i;
    //number of points
    int n=numberOfPoints;
    n = n-1;
    //drawing bezier curve
    for(t = 0; t<=1;t=t+0.001)
    {
        x=0; y=0;
        for(i = 0 ; i<=n; i++)
        {
            x = x + (comb(n,i) * pow(1-t, n-i) * pow(t,i) * points[i].x );
            y = y + (comb(n,i) * pow(1-t, n-i) * pow(t,i) * points[i].y );
        }
        putpixel(400+20*x, 400-20*y, WHITE);
    }
}


int main() {
    //-------- Reading points from .txt file and copying them to points struct array------------//
    struct Point points[50];
    FILE *pointFile;
    //dosya yerini ve yapmak istediðim iþlem "r for reading"
    pointFile = fopen("C:\\Users\\h\\Desktop\\MECTest.txt","r");
    int pointCounter=0;
    int i=0;
    if(pointFile==NULL)
    {
        printf("Dosya bulunamadi.");
    }
    while(!feof(pointFile))
    {
        pointCounter++;
        fscanf(pointFile, "{%f,%f},", &points[i].x,&points[i].y);
        i++;
    }
    //Number of points:
    int numberOfPoints = pointCounter-1;
    noktaSayisi = numberOfPoints;
    printf("Number of points: %d\n", numberOfPoints);
    for(i = 0; i < numberOfPoints ; i++)
    {
        printf("{%.0f,%.0f}\n", points[i].x, points[i].y);
    }
    fclose(pointFile);
    //-------------------------------------------------------------------------------------------//


    //------------------------------------ Opening the graph ------------------------------------//
    initwindow(800,800);
    //Kordinat sistemini çizelim. InitWindow 'a göre ayarlanmistir(800x800)
    kordinatDuzlemi();
    //Noktalarimizi yazdiralim.
    yazdirNokta(points, numberOfPoints);


    //Cemberimizi cizdirmeye baslayalim
    if(numberOfPoints==0)
    {
        closegraph();
        printf("Lutfen nokta giriniz!\n");
    }
    if(numberOfPoints==1)
    {
        printf("Bir noktayi kapsayacak en kucuk cember kendisidir!\n");
        getch();
        closegraph();
    }
    if(numberOfPoints==2)
    {

        Circle twoPoint = twoPointsCircle(points[0], points[1]);
        if(circleWithAllPoints(twoPoint, points, numberOfPoints))
        {
            circle(400+twoPoint.C.x*20, 400-twoPoint.C.y*20, 20*twoPoint.r);
            outtextxy(400 + twoPoint.C.x * 20, 400 - twoPoint.C.y * 20, "M"); //Merkez Noktasý
            //yaricap cizgisi
            moveto(400+20*twoPoint.C.x, 400 - 20*twoPoint.C.y);
            lineto(400+20*twoPoint.C.x + twoPoint.r*20 , 400 - 20*twoPoint.C.y);
            spline(points, numberOfPoints);
            printf("Cember butun noktalari kapsamaktadir!\n");
            printf("Grafikte bozulmalar olabilir. \nBunun sebebi circle() fonksiyonunun integer deger kabul etmesinden dogan hata payidir.\n");
            getch();
            closegraph();
        }
    }
    if(numberOfPoints==3)
    {
        Circle threePoint = minimumEnclosingCircle(points, numberOfPoints);
        circle(400 + threePoint.C.x * 20, 400 - threePoint.C.y * 20, threePoint.r * 20);
        outtextxy(400 + threePoint.C.x * 20, 400 - threePoint.C.y * 20, "M"); //Merkez Noktasý
        //yaricap cizgisi
        moveto(400+20*threePoint.C.x, 400 - 20*threePoint.C.y);
        lineto(400+20*threePoint.C.x + threePoint.r*20 , 400 - 20*threePoint.C.y);
        spline(points, numberOfPoints);
        printf("Cember butun noktalari kapsamaktadir!\n");
        printf("Grafikte bozulmalar olabilir. \nBunun sebebi circle() fonksiyonunun integer deger kabul etmesinden dogan hata payidir.\n");
        getch();
        closegraph();
    }
    if(numberOfPoints>3)
    {
        doCombination(points, numberOfPoints, 3);
        printf("Cember Merkezi : (%.1f,%.1f)\nYaricapi:%.1f\n", MEC.C.x, MEC.C.y, MEC.r);
        circle(400+20*MEC.C.x, 400 - 20*MEC.C.y, MEC.r*20);
        outtextxy(400 + MEC.C.x * 20, 400 - MEC.C.y * 20, "M"); //Merkez Noktasý
        //yaricap cizgisi
        moveto(400+20*MEC.C.x, 400 - 20*MEC.C.y);
        lineto(400+20*MEC.C.x + MEC.r*20 , 400 - 20*MEC.C.y);
        spline(points, numberOfPoints);
        printf("Cember butun noktalari kapsamaktadir!\n");
        printf("Grafikte bozulmalar olabilir. \nBunun sebebi circle() fonksiyonunun integer deger kabul etmesinden dogan hata payidir.\n");
        getch();
        closegraph();
    }
    return 0;
}

