#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <math.h>

bool degerlerAtandi=false;

void DrawXYAxis()
{
    line(0,375,2*375,375);      // x eksenini cizer
    line(375,0,375,2*375);      // y eksenini cizer

    for(int i = 0; i < 751; i+=15)   // x ve y ekseni uzerindeki cizgileri cizer
    {
        if(i%75==0)
        {
            line(i,380,i,370);  // x ekseni üstündeki 5 in katı olan her noktaya bir çizgi çeker
            line(370,i,380,i);  // y ekseni üstündeki 5 in katı olan her noktaya bir çizgi çeker
        }
        else
        {
            line(i,377,i,373);  // x ekseni üstündeki 5 in katı olmayan her noktaya bir çizgi çeker
            line(373,i,377,i);  // y ekseni üstündeki 5 in katı olmayan her noktaya bir çizgi çeker
        }
    }

    outtextxy(0,375+5,"-25");               // bu fonksiyonun icindeki geri kalan doklar x  ve y eksenindeki
    outtextxy(75-10,375+5,"-20");           // her 5 in katı olan noktaya gelen uzun cizgilerin degerini
    outtextxy(75*2-10,375+5,"-15");         // yazdirmaya yarar
    outtextxy(75*3-10,375+5,"-10");
    outtextxy(75*4-6,375+5,"-5");

    outtextxy(2*375-15,375+6,"25");
    outtextxy(2*375-(75)-7,375+5,"20");
    outtextxy(2*375-(75*2)-7,375+5,"15");
    outtextxy(2*375-(75*3)-7,375+5,"10");
    outtextxy(2*375-(75*4)-3,375+5,"5");

    outtextxy(375-22,0,"25");
    outtextxy(375-22,75-7,"20");
    outtextxy(375-22,75*2-7,"15");
    outtextxy(375-22,75*3-7,"10");
    outtextxy(375-15,75*4-7,"5");

    outtextxy(375-27,2*375-14,"-25");
    outtextxy(375-27,2*375-75-8,"-20");
    outtextxy(375-27,2*375-(75*2)-8,"-15");
    outtextxy(375-27,2*375-(75*3)-8,"-10");
    outtextxy(375-20,2*375-(75*4)-8,"-5");
}

void DrawCircle(double centerX,double centerY, double radius)
{
    setcolor(YELLOW);
    setfillstyle(1,YELLOW);
    circle(375+centerX*15, 375- centerY*15, radius*15); // x,y,yariCap  degerlerinden yararlanarak cemberi cizer
    fillellipse(375+centerX*15,375-centerY*15,4,4); // merkez noktasi
    char msg[128];
    sprintf(msg, "r=%.2lf", radius);
    outtextxy(375+centerX*15+5, 375- centerY*15+5,msg);
}

void DrawPoints(int noktalar[1000][2],int noktaSayisi)  // noktalari cizer
{
    for(int i=0; i<noktaSayisi; i++)
    {
        fillellipse(375+noktalar[i][0]*15,375-noktalar[i][1]*15,4,4);           // cember daha görülebilir olsun yarıcapı 4 pixel olan bi daire olarak cizilir ve ici boyanır
        //printf("cizilen noktalar  --> %d,%d\n",noktalar[i][0],noktalar[i][1]);
    }
}

double FindTheDistanceBetweenTwoPoints(double x1, double y1, double x2, double y2)  // koordinatları verilen 2 nokta arasındaki uzaklıgı döndürür
{
    double distance,x,y;
    x = x2-x1;
    y = y2-y1;
    distance = sqrt((x*x)+(y*y));
    return distance;
}

double MidPointOfTwoPoint(double a, double b)   // verilen iki sayinin ortalamasını döndürür
{
    // bunu iki noktanın orta noktasını bulmak icin x ve y
    double midPoint;                            // degerleri icin ayri ayri kullandık
    midPoint = (a + b) / 2;
    return midPoint;
}
void FindCircleFromThreePoint(int noktalar[1000][2],int noktaSayisi)
{

    int x1,x2,x3,y1,y2,y3;
    double x12,x13,y12,y13,y31,y21,x31,x21,sx13,sy13,sx21,sy21,f,g,c,h,k,r,sqr_of_r,lastCenterX,lastCenterY,smallestRadius = 999999;
    for(int i=0; i<noktaSayisi-2; i++)
    {
        for(int j=i+1; j<noktaSayisi-1; j++)        // burdaki 3 lu for yapisi verilen noktaların tamamının 3 lu kombinasyonlarına ulasılmasını saglıyor
        {
            for(int t=j+1; t<noktaSayisi; t++)
            {
                //printf("\n-------------------- %d - %d - %d ------------------------------",i,j,t);

                x1=noktalar[i][0];      // 3 noktanın verileri alınıp cemberin degerleri bulunuyor
                y1=noktalar[i][1];
                x2=noktalar[j][0];
                y2=noktalar[j][1];
                x3=noktalar[t][0];
                y3=noktalar[t][1];

                x12 = x1 - x2;
                x13 = x1 - x3;

                y12 = y1 - y2;
                y13 = y1 - y3;

                y31 = y3 - y1;
                y21 = y2 - y1;

                x31 = x3 - x1;
                x21 = x2 - x1;

                // x1^2 - x3^2
                sx13 = (double)(pow(x1, 2) - pow(x3, 2));

                // y1^2 - y3^2
                sy13 = (double)(pow(y1, 2) - pow(y3, 2));

                sx21 = (double)(pow(x2, 2) - pow(x1, 2));

                sy21 = (double)(pow(y2, 2) - pow(y1, 2));

                f = ((sx13) * (x12)
                     + (sy13) * (x12)
                     + (sx21) * (x13)
                     + (sy21) * (x13))
                    / (2 * ((y31) * (x12) - (y21) * (x13)));

                g = ((sx13) * (y12)
                     + (sy13) * (y12)
                     + (sx21) * (y13)
                     + (sy21) * (y13))
                    / (2 * ((x31) * (y12) - (x21) * (y13)));

                c = -(double)pow(x1, 2) - (double)pow(y1, 2) -  2 * g * x1 - 2 * f * y1;

                // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0
                // where centre is (h = -g, k = -f) and radius r
                // as r^2 = h^2 + k^2 - c
                h = -g;
                k = -f;
                sqr_of_r = h * h + k * k - c;

                // r is the radius
                r = sqrt(sqr_of_r);
                degerlerAtandi = true;
                for (int i = 0; i < noktaSayisi ; i++)
                {
                    //printf("\nuzaklik, r --> %lf,   %lf",FindTheDistanceBetweenTwoPoints(h,k,noktalar[i][0],noktalar[i][1]), r);

                    if(FindTheDistanceBetweenTwoPoints(h,k,noktalar[i][0],noktalar[i][1]) > r)      //cemberin merkezine girilen tum noktalarin uzaklığı tespit edilip
                    {
                        // yaricaptan buyuk olup olmadıkları kontrol edilir
                        degerlerAtandi = false;                                                     // buyuk iseler cemberin dısında kalacaklarından degerlerin uygun olmadıgı
                        //printf("\ndisarda nokta var");                                            // tespit edilir
                    }
                }
                if(degerlerAtandi && r<=smallestRadius) // cemberin dısında nokta yoksa ve bulunan yaricap bi öncekinden daha kucukse
                {
                    // degerler kaydedilir. Tum ihtimaller denendikten sonra kalan en kucuk yarıcaplı
                    //printf("\n\nicerde\n\n");         // tum noktaları icine alan daire cevabımızdır
                    smallestRadius =r;
                    lastCenterX = h;
                    lastCenterY = k;
                }
            }
        }
    }
    DrawCircle(lastCenterX,lastCenterY,smallestRadius);
    printf("\ncemberin merkezi --> %lf , %lf\ncemberin yaricapi --> %lf",lastCenterX,lastCenterY,smallestRadius);

}
void FindCircleFromTwoPoint(int noktalar[1000][2],int noktaSayisi)
{
    double ikiNoktaArasiUzaklik,centerX,centerY,smallestRaidus=999999,lastX,lastY;

    for(int i=0; i<noktaSayisi-1; i++)      // ilk iki for tüm 2 li nokta kombinasyonlarını denemek icin
    {
        for(int j=i+1; j<noktaSayisi; j++)
        {
            degerlerAtandi = false;
            centerX = MidPointOfTwoPoint(noktalar[i][0],noktalar[j][0] );       // denenen 2 noktanın merkezinin x i
            centerY = MidPointOfTwoPoint( noktalar[i][1],noktalar[j][1] );      // denenen 2 noktanın merkezinin y si
            ikiNoktaArasiUzaklik = FindTheDistanceBetweenTwoPoints(noktalar[i][0], noktalar[i][1], noktalar[j][0], noktalar[j][1]);     // denenen 2 nokta icin cap

            //printf("\n------- %d %d ------------",i,j);

            //printf("\n iki nokta arasi uzaklik / 2 , smallest radius ---> %lf , %lf ",ikiNoktaArasiUzaklik / 2, smallestRaidus);
            if(ikiNoktaArasiUzaklik / 2 <= smallestRaidus) // bulunan yeni cemberin eski cemberden daha kucuk olup olmadıgını kontrol eder
            {

                degerlerAtandi = true;
                for (int k = 0; k < noktaSayisi ; k++)      // bu forun icinde tum noktaların cemberin icinde olup olmadıgı kontrol ediliyor
                {
                    if(FindTheDistanceBetweenTwoPoints(centerX,centerY,noktalar[k][0],noktalar[k][1]) > ikiNoktaArasiUzaklik / 2 )
                    {
                        //printf("\ndisardaki nokta indexi --> %d",k);
                        degerlerAtandi = false;
                    }
                }
                if( degerlerAtandi) // disarda hic nokta yoksa buraya girer
                {
                    //printf("\nin");
                    lastX = centerX;
                    lastY = centerY;
                    smallestRaidus =  ikiNoktaArasiUzaklik / 2;
                    //printf("---- %lf %lf %lf-------",lastX,lastY,smallestRaidus);
                }
            }
        }
    }

    degerlerAtandi = true;
    for (int k = 0; k < noktaSayisi ; k++)      // bu forun icinde tum noktaların cemberin icinde olup olmadıgı kontrol ediliyor
    {
        if(FindTheDistanceBetweenTwoPoints(lastX,lastY,noktalar[k][0],noktalar[k][1]) > smallestRaidus )
        {
            //printf("\ndisardaki nokta indexi --> %d",k);
            degerlerAtandi = false;
        }
    }

    if(degerlerAtandi && smallestRaidus < 999998)
    {
        DrawCircle(lastX,lastY,smallestRaidus);
        printf("\ncemberin merkezi --> %lf , %lf\ncemberin yaricapi --> %lf",lastX,lastY,smallestRaidus);
    }
    else
    {
        //printf("\n3 noktadan cizildi\n");
        // 3 noktanin geçtigi çemberi çiz
        FindCircleFromThreePoint(noktalar,noktaSayisi);
    }
}

int fact(int n){
    if(n==0)
        return 1;
    else
        return n*fact(n-1);
}

int comb(int n, int r){
    return (fact(n)/(fact(n-r)*fact(r)));
}

void DrawBezierCurve(int noktalar[1000][2],int noktaSayisi){            // https://www.youtube.com/watch?v=hqONlh0YTeA
    // drawing the beizer curve
    double x,y;
    for(double t= 0;t<=1;t+=0.0001){
        x=0;
        y=0;
        for(int i=0;i<noktaSayisi;i++){
            x = x+ ( comb(noktaSayisi-1,i) * pow(1-t,noktaSayisi-1-i) * pow (t,i) * noktalar[i][0]);
            y = y+ ( comb(noktaSayisi-1,i) * pow(1-t,noktaSayisi-1-i) * pow (t,i) * noktalar[i][1]);
        }
        putpixel(375+x*15,375-y*15,RED);
    }
}


int main()
{
    FILE *dosya;
    char dosyadanOkunan[1000];
    int noktalar[1000][2];
    int i =0,j=0;
    if ((dosya = fopen("noktalar.txt", "r")) == NULL)   // dosya değişkenini açar, açamazsa mesaj yazdırır
    {
        printf("dosya acilamadi!\n");
        exit(1);
    }
    fscanf(dosya, "%[^\n]", &dosyadanOkunan);       //dosyayı satır sonuna kadar okur
    //printf("Data from the file:\n%s\n", dosyadanOkunan);

    char * pch;
    pch = strtok (dosyadanOkunan,",(){}");         // dosyadan okunanları

    fclose(dosya);      //dosyayı kapar

    while (pch != NULL)
    {
        noktalar[j][i%2] = atoi(pch); // dosyadan okunan string degeri integer a cevirir
        if(noktalar[j][i%2] == NULL)  // eger koordinatlardan biri girilmemişse onu tespit eder
        {
            noktalar[j][i%2] = 0;       // tespit edilen degere 0 atar
        }
        pch = strtok (NULL, ",(){}");  // dosyadan okunanları çift tirnak icindeki karakterlere göre böler
        i++;
        if(i%2==0)
        {
            j++;            // dosyada kaç nokta olduğu bilgisini while dan cikinca tutar
        }
    }
    // https://www.geeksforgeeks.org/draw-circle-c-graphics/

    initwindow(751, 751); // sağ ve alt gözüksün diye 750 yerine 751
    DrawXYAxis();
    DrawPoints(noktalar,j);

    if(j==0)
    {
        printf("Nokta girmediniz.");
    }
    else if( j == 1)
    {
        DrawCircle(noktalar[0][0],noktalar[0][1],0);
        printf("\ncemberin merkezi --> %lf,%lf\ncemberin yaricapi --> 0",noktalar[0][0],noktalar[0][1]);

    }
    else if(j == 2)
    {
        DrawCircle(MidPointOfTwoPoint(noktalar[0][0],noktalar[1][0])
                   ,MidPointOfTwoPoint(noktalar[0][1],noktalar[1][1])
                   ,FindTheDistanceBetweenTwoPoints(noktalar[0][0]
                           ,noktalar[0][1],noktalar[1][0],noktalar[1][1]) / 2);

        printf("\ncemberin merkezi --> %lf,%lf\ncemberin yaricapi --> %lf"
               ,MidPointOfTwoPoint(noktalar[0][0],noktalar[1][0])
               ,MidPointOfTwoPoint(noktalar[0][1],noktalar[1][1])
               ,FindTheDistanceBetweenTwoPoints(noktalar[0][0]
                                                ,noktalar[0][1],noktalar[1][0],noktalar[1][1]) / 2);
    }
    else
    {
        FindCircleFromTwoPoint(noktalar,j);
    }

    DrawBezierCurve(noktalar,j);


    getch(); // grafik arayuzun otomatik kapanmasini engeller

    // closegraph function closes the
    // graphics mode and deallocates
    // all memory allocated by
    // graphics system .
    closegraph();

    return 0;
}

