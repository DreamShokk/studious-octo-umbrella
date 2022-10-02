int strToInt(char* String){
    int val=0;
    int isNeg=1;
    if(*String=='-'){
        String++;
        isNeg=-1;
    }
        int length=strLength(String);
        for(int i=0;i<length;i++)
            val+=(String[i]-'0')*Pow(10,abs(i-(length-1)));
        return val*isNeg;
    
    
}
double Pow(double num, int toPow){
    double result=num;
    if(toPow==0)return 1;
    for(int i=1;i<toPow;i++){
        result*=num;
    }
    return result;

}
int abs(int num){
    if(num<0)return num*(-1);
    return num;
}

void getSubString(char* subStringTo,char* String, int start, int end){
    int i;
    for(i=start;i<=end;i++)
    subStringTo[i-start]=String[i];
}
void copyString(char* copyfrom,char* copyto){
    while(*copyfrom){
        *copyto=*copyfrom;
        copyto++;
        copyfrom++;
    }
    *copyto=0;
}
inline int isNumber(char ch){
    return ch>='0'&&ch<='9';
}
int isStringNumber(char* String){
    int L=strLength(String);
    int current=0;
    while(String[current]){
        if(isNumber(String[current]))
        current++;
        else
        break;
    }
    if(current<L)
        return 0;
    else
        return 1;
        
}
inline int isLeapYear(int year){
    return (year%4==0&&year%100!=0)||year%400==0;
}
int datumCheck(char* datum,char* prevDatum){
    char y[5]={0};
    char m[3]={0};
    char d[3]={0};
    int honapok[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int l=0;

    if(*(datum+4)!='.'||*(datum+7)!='.'||*(datum+10)!='.')
        return -1;

    while(datum[l]){
        if(!isNumber(datum[l])&&(l!=4&&l!=7&&l!=10))
        return 0;
        l++;
    }
    getSubString(m,datum,5,6);
    int _m=strToInt(m);
    if(_m<1||_m>12)
        return 2;
    getSubString(y,datum,0,3);
    int _y=strToInt(y);
    getSubString(d,datum,8,9);
    int _d=strToInt(d);
    if(_d<1||_d>31)
        return 3;
    if(isLeapYear(_y))
        honapok[1]=29;
    if(_d>honapok[(_m-1)])
        return 3;
    
    char py[5]={0};
    char pm[3]={0};
    char pd[3]={0};
    getSubString(py,prevDatum,0,3);
    getSubString(pm,prevDatum,5,6);
    getSubString(pd,prevDatum,8,9);
    if(strToInt(py)>_y)
        return 4;
    if(strToInt(py)==_y)
        if(strToInt(pm)>_m)
            return 4;
        else if(strToInt(pd)<_d)
            return 4;
    return 1;
}

void datumInit(char* datum,char* prevDatum){
    char datein[12];
    do{
    printf("Adja meg a mai datumot (%11s az utolso elmentett hasznalati datum, formatuma egyezzen meg vele): ",prevDatum);
    scanf("%11s",datein);
    switch(datumCheck(datein,prevDatum)){
        case 1:copyString(datein,datum);system("clear");;return;
        case -1:printf("Hibas elvalaszto jel(ek) - nem megfelelo ido formatum.\n");break;
        case 0: printf("Tartalmaz a datum nem-szamot - nem megfelelo adat.\n");break;
        case 2:printf("Rossz honapszam - nem megfelelo adat.\n");break;
        case 3:printf("Rossz napszam - nem megfelelo adat.\n");
        case 4:printf("Nem adhat meg regebbi datumot, mint ami az utolso hasznalatkor lett megadva.\n");
    }
    printf("Megprobalja ujra (y/n)? ");
    getchar();
    if(getchar()=='n'){
        system("clear");
        printf("Viszont latasra!\n");
        exit(0);
    }
    system("clear");
    }while(datumCheck(datein,prevDatum)!=1);
}
int fileInit(char* filename,FILE** fp){
    int run=0;
    do{
        run=0;
        printf("Adja meg a beolvasando file nevet (max 50 karakter): ");
        scanf("%50s",filename);
        *fp=fopen(filename,"r");

        if(!*fp){
            printf("A fajl nem letezik. Megprobalja ujra? (y/n)\n");
            getchar();
            if(getchar()=='n')
                exit(-1);
            else run=1;
    }
    system("clear");
    }while(run==1);
}
void getData(FILE* fp,ugyfel** root,char* prevDatum){

    fscanf(fp,"%11s\n",prevDatum);

    int a=0;
    do{
        char email[26];
        char name[26];
        char tel[26];
        char funds[26];
        char date[26];
        char intr[26];
        a=fscanf(fp,"%25[^ ,\n\t],%25[^ ,\n\t],%25[^ ,\n\t],%25[^ ,\n\t],%25[^ ,\n\t],%25[^ ,\n\t]\n",name,email,tel,funds,date,intr);
        if(a==6)
        addUgyfel(*root,name,email,tel,funds,date,intr);
    }while(a==6);
}
void kamatCalc(ugyfel* kalkulalando){
    char* nEv=malloc(sizeof(char)*3);
    system("clear");
    printf("Hany evvel kesobbi potencialis kamatjovairast tekintene meg? (1-99) ");
    scanf("%2s",nEv);
    if(isStringNumber(nEv)){
        double kamatszorzo=1+strToInt(kalkulalando->intr)/100.0;
        double kamatkitevo=Pow(kamatszorzo,strToInt(nEv));
        double res=strToInt(kalkulalando->funds)*kamatkitevo;
        printf("A potencialis osszeg, mellyel rendelkezne %s ev mulva: %.0f",nEv,res);
    }else
    printf("A megadott adat nem egy megfelelo szam. Problaja meg ujra. ");
    printf("\nA folytatasert nyomjon entert. ");
    getchar();
    getchar();
    free(nEv);
}
void fileWrite(ugyfel* root,char* filename, char* datum){
    printf("A modositasokat el szeretne menteni a %s file-ba? (y/n) ");
    getchar();
    if(getchar()!='n'){
        FILE* fp;
        fp=fopen(filename,"w");
        fprintf(fp,"%s\n",datum);
        ugyfel* current=root->next;
        while(current){
            fprintf(fp,"%s,%s,%s,%s,%s,%s\n", current->name,current->emailaddr,current->tel,current->funds,current->date,current->intr);
            current=current->next;
        }
        fclose(fp);
    }
    
}
void ugyfelekMenu(ugyfel* start){
    system("clear");
    int i=0;
    ugyfel* current=start;
    while(current){
        printf("%-25s%-25s%-25s%-25s%-25s%-25s\n", current->name,current->emailaddr,current->tel,current->funds,current->date,current->intr);
        current=current->next;
        i++;
    }
    printf("\nUgyfellista %d elembol all.\n",i-1);

    printf("Folytatasert nyomjon entert. ");

    getchar();
    getchar();

}
int strLength(char* String){
    int length=0;
    while(String[length])
    length++;
    return length;
}
int stringEquals(char* String1, char* String2){
    if(strLength(String1)==strLength(String2)){
        int l=strLength(String1);
        for(int i=0; i<l;i++){
            if(*(String1+i)!=*(String2+i))
            return 0;
        }
        return 1;
    }
    return 0;
}
int isPresent(ugyfel*root, char* nev){
    ugyfel* current=root;
    while(current){
        if(stringEquals(current->name,nev))
            return 1;
        current=current->next;
    }
    return 0;
}
void utalas(ugyfel* currentugyfel,ugyfel* root,char* datum){
    system("clear");
    printf("%s utalasi/szamlazasi urlapja\n",currentugyfel->name);
    char* kedvezmenyezett=malloc(26);
    int toUtal=0;
        while(1){
            printf("%s","kedvezmenyezett/szamlazott neve: ");
            scanf("%25s",kedvezmenyezett);
            if(!isPresent(root,kedvezmenyezett)){
                printf("Az adott nev nem talalhato. Megprobalja ujra? (y/n)");
                getchar();
                if(getchar()=='n'){
                    return;
                }
            }else if(stringEquals(currentugyfel->name,kedvezmenyezett)){
                    printf("A megadott azonosito onmagara utal. Megprobalja ujra? (y/n)");
                    getchar();
                    if(getchar()=='n'){
                        return;
                    }
            }else break;
        }
    
        ugyfel* _kedvezmenyezett=getUgyfelByNev(root,kedvezmenyezett);
        free(kedvezmenyezett);
        while(1){
            printf("Szamlazasert negativ jelzovel, utalasert onmagaban adja meg az osszeget: ");
            scanf("%d",&toUtal);
            if(toUtal==0){
                printf("Nem adott meg erteket. Megprobalja ujra? (y/n)");
                getchar();
                if(getchar()=='n')
                    break;
            }else 
            if(toUtal>0){
            if(strToInt(currentugyfel->funds)<toUtal){
                printf("Nincs elegendo egyenlege ezen utalashoz. Megprobalja ujra? (y/n)\n");
                getchar();
                if(getchar()=='n')
                    break;
            }else{
                printf("Megerosites: %d utalasa %s-tol %s-nek (y/n)? ",toUtal,currentugyfel->name,_kedvezmenyezett->name);
                getchar();
                if(getchar()!='n'){
                    int res=strToInt(currentugyfel->funds)-toUtal;
                    sprintf(currentugyfel->funds,"%d",res);
                    copyString(datum,currentugyfel->date);

                    res=strToInt(_kedvezmenyezett->funds)+toUtal;
                    sprintf(_kedvezmenyezett->funds,"%d",res);
                    copyString(datum,_kedvezmenyezett->date);

                    break;
                }else
                break;
            }
        }else{
            if(strToInt(_kedvezmenyezett->funds)<abs(toUtal)){
                printf("Nincs elegendo egyenlege a szamlazottnak. Konyvlejuk el tartozaskent(y), vagy sztornozzuk a szamlazast(n)? (y/n)\n");
                getchar();
                if(getchar()=='n')
                    break;
            }
                printf("Megerosites: %d szamlazas %s reszere %s-tol? (y/n) ",abs(toUtal),currentugyfel->name,_kedvezmenyezett->name);
                getchar();
                if(getchar()!='n'){
                    int res=strToInt(currentugyfel->funds)-toUtal;
                    sprintf(currentugyfel->funds,"%d",res);
                
                    res=strToInt(_kedvezmenyezett->funds)+toUtal;
                    sprintf(_kedvezmenyezett->funds,"%d",res);
            
                }
                break;
            
        }
        }
}
void removeUgyfel(ugyfel* root){
    ugyfel* previous=root;
    ugyfel* toRemove=root->next;
    char* buffer=malloc(sizeof(char)*26);
    int run=1;
    while(run==1){
        system("clear");
        printf("Adja meg az eltavolitando ugyfel azonositojat: ");
        scanf("%25s",buffer);
        if(!isPresent(root,buffer)||stringEquals(buffer,"NEV")){
            printf("A megadott ugyfel nem talalhato. Megprobalja ujra? (y/n) ");
            getchar();
            if(getchar()=='n')
                run=0;
        }else run=2;
    }
    if(run==2){
        printf("Megerosites: %s torlese az adatbazisbol? (y/n)",buffer);
        getchar();
        if(getchar()!='n'){
        while(!stringEquals(toRemove->name,buffer)){
            toRemove=toRemove->next;
            previous=previous->next;
        }
        
        free(toRemove->name);
        free(toRemove->emailaddr);
        free(toRemove->tel);
        free(toRemove->funds);
        free(toRemove->date);
        free(toRemove->intr);
        if(toRemove->next==NULL)
            previous->next=NULL;
        else
            previous->next=toRemove->next;
        free(toRemove);
        printf("Az ugyfel sikeresen torlesre kerult. A penzugyekkel kapcsolatban es szerzodesbontasrol levelben ertesitjuk. Nyomjon entert a folytatashoz. ");
        getchar();
        }
    }
    free(buffer);
}

void sajatpenzugyekMenu(ugyfel* root,char* datum){
    char* currentUgyfel=malloc(26);
    
    while(1){
    system("clear");
    printf("Adja meg az ugyfelazonosito nevet: ");
    scanf("%25s",currentUgyfel);
    if(!isPresent(root,currentUgyfel)||stringEquals(currentUgyfel,"NEV")){
        printf("A megadott azonosito nem letezik az adatbazisban. Megprobalja ujra? (y/n)");
        getchar();
        if(getchar()=='n'){
            break;
        }
        
    }else{
        ugyfel* selected=getUgyfelByNev(root, currentUgyfel);
        penzugyekMenu(selected,root,datum);
        break;
    }
}
}
void kplekotes(ugyfel* currentUgyfel,char* datum){
    char buffer[26];
    int run=1;
    while(run){
        system("clear");
        printf("Mennyi penzt kotne le? \n");
        scanf("%25s",buffer);
        int l=0;
        while(buffer[l]){
            if(buffer[l]<'0'||buffer[l]>'9'){
                printf("A megadott ertek tartalmaz nem szam karakter. Megprobalja ujra? (y/n) ");
                getchar();
                if(getchar()=='n'){
                    break;
                    run=-1;
                }
            }
            l++;
        }
        if(run==1){

                sprintf(currentUgyfel->funds,"%d",(strToInt(currentUgyfel->funds)+strToInt(buffer)));
                copyString(datum,currentUgyfel->date);
                run=0;
            }
            
    }
}
void penzugyekMenu(ugyfel* currentUgyfel,ugyfel* root,char* datum){
    int run=1;
    while(run){
    system("clear");
    printf("Jelenlegi ugyfel: %-25s\nJelenlegi egyenleg: %-25s\n",currentUgyfel->name,currentUgyfel->funds);
    if(strToInt(currentUgyfel->funds)<0){
        printf("\nFigyelem! Onnek tartozasa van. Mielott utalhatna vagy szamlazhatna, torlessze tartozasat!\n\nVallassza ki a szamara megfelelo ugyintezesi pontot az alabbiak kozul: \n");
        printf("%-20s%-20s\n", "1. Adatok kezelese","2. Kezpenz lekotes");
    printf("0. kilepes\n");
    switch(getchar()){
        case '0':run=0;break;
        case '1':adatkezeles(currentUgyfel,root,datum);break;
        case '2':kplekotes(currentUgyfel,datum);break;
        case '\n':break;
        default:printf("A megadott opcio nem letezik. Nyomjon entert a folytatáshoz.\n");getchar();
    }
    }else{
    printf("Vallassza ki a szamara megfelelo ugyintezesi pontot az alabbiak kozul: \n");
    printf("%-20s%-20s%-20s%-20s\n", "1. Adatok kezelese","2 Utalas/Szamlazas","3. Kezpenz lekotes","4. Kamat-kalkulator");
    printf("0. kilepes\n");
    switch(getchar()){
        case '0':run=0;break;
        case '1':adatkezeles(currentUgyfel,root,datum);break;
        case '2':utalas(currentUgyfel,root,datum);break;
        case '3':kplekotes(currentUgyfel,datum);break;
        case '4':kamatCalc(currentUgyfel);break;
        case '\n':break;
        default:printf("A megadott opcio nem letezik. Nyomjon entert a folytatáshoz.\n");getchar();
    }
    }
    }
}
void adatkezeles(ugyfel* currentUgyfel,ugyfel* root,char* datum){
    int run=1;
    getchar();
    while(run){
        system("clear");
        printf("%s, kerem valasszon az alabbi adatmodositasi lehetosegek kozul: \n",currentUgyfel->name);
        printf("%-30s%-25s%-25s%-25s\n","0. Vissza az ugyintezeshez","1. Azonosito modositas","2. E-mail cim modositas","3. Telefonszam modositas");
        switch(getchar()){
            case '0':run=0;break;
            case '1':azModositas(currentUgyfel,root,datum);break;
            case '2':emailModositas(currentUgyfel,root,datum);break;
            case '3':telModositas(currentUgyfel,root,datum);break;
            case '\n':break;;
            default: printf("A megadott funkcio nem letezik. A folytatashoz nyomjon entert.\n");getchar();
        }
    }
}
void azModositas(ugyfel* currentugyfel,ugyfel* root,char* datum){
    char ujnev[26];
    int run=1;
    while(run){
    system("clear");
    printf("Adja meg a kivant uj azonositot, mely egy egysegbol all (space helyett alkalmazzon \'_\'-at!)\n");
    scanf("%25s",ujnev);
    if(isPresent(root, ujnev)){
        printf("A megadott nev mar szerepel az adatbazisban / ugyan azt a nevet adata meg. Megprobalja ujra? (y/n)\n");
        getchar();
        if(getchar()=='n')
        run=0;
    }else{
        printf("Megerosites: levaltja %s azonositojat %s uj azonositora? (y/n)\n",currentugyfel->name,ujnev);
        getchar();
        if(getchar()!='n'){
            copyString(ujnev,currentugyfel->name);
            copyString(datum,currentugyfel->date);
        }
        run=0;
    }
    }

}
void telModositas(ugyfel* currentugyfel, ugyfel* root,char* datum){
    char ujTel[26];
    
    while(1){
    system("clear");
    printf("Adja meg az uj telefonszamat, mely formatuma '+telefonszam' vagy csak 'telefonszam' :\n");
    scanf("%25s",ujTel);
    int isValid=telCheck(ujTel);
    if(isValid==1){
        printf("Megerosites: levaltja %s telefonszamat %s uj telefonszamra? (y/n)\n",currentugyfel->tel,ujTel);
        getchar();
        if(getchar()!='n'){
            copyString(ujTel,currentugyfel->tel);
            copyString(datum,currentugyfel->date);
        }
        break;
    }else
    if(isValid==0){
        printf("A megadott szam tul rovid - megprobalja ujra? (y/n)");
        getchar();
        if(getchar()=='n')break;
    }else{
        printf("A megadott szam tartalmaz nem megfelelo karaktert. Megproblaja ujra? (y/n)\n");
        getchar();
        if(getchar()=='n')
        break;
    }
    }
    
    
}
int telCheck(char* number){
    if(strLength(number)<6)
        return 0;
    if(*number=='+')
        number++;
    while(*number){
        if(*number<'0'||*number>'9')
            return -1;
        number++;
    }
    return 1;
}
void emailModositas(ugyfel* currentugyfel,ugyfel* root,char* datum){
    char ujmail[26];
    while(1){
    system("clear");
    printf("Adja meg az uj e-mail cimet, mely formatuma felhasznalonev@domain.com :\n");
    scanf("%25s",ujmail);
    if(mailCheck(ujmail)){
        printf("Megerosites: levaltja %s e-mail cimet %s uj emailre? (y/n)\n",currentugyfel->emailaddr,ujmail);
        getchar();
        if(getchar()!='n'){
            copyString(ujmail,currentugyfel->emailaddr);
            copyString(datum, currentugyfel->date);
        }
        break;
    }else{
        printf("A megadott e-mail cim nem megfelelo. Megproblaja ujra? (y/n)\n");
        getchar();
        if(getchar()=='n')
        break;
    }
    }
}
int mailCheck(char* mail){
    int indexofAt=strCharIndex(mail,'@');
    int indexofDot;
    if(indexofAt>0){
        indexofDot=strCharIndex(mail+indexofAt,'.');
    }else 
        return 0;
    if(indexofDot<=1||indexofAt+indexofDot==strLength(mail)-1)
        return 0;
    return 1;
    
}
int strCharIndex(char* String, char containedChar){
    int i=0;
    while(*(String+i)){
        if(*(String+i)==containedChar)
            return i;
        i++;
    }
    return -1;
}
void callMenu(char* date, char* filename, FILE *fp, ugyfel* datalist){
    system("clear");
    getchar();
    int choice=0;
    do{
        char* disz={"______________________________________________________"};
        printf("%6s%11s%s%5s%s\n\n","datum:",date,disz,"File:",filename);
        printf("%-20s%-20s%-20s%-20s\n\n","1. Ugyfelek","2. Sajat penzugyek","3. Uj ugyfel","4. Ugyfel torlese");
        printf("%s%s%s%s\n","Menu",disz,"__________________","0. kilepes");
        printf("Valasztott opcio: \n");
        choice=getchar();
        if(choice!='0'){
            switch(choice){
                case '1':ugyfelekMenu(datalist);break;
                case '2':sajatpenzugyekMenu(datalist,date);break;
                case '3':ujUgyfel(datalist,date);break;
                case '4':removeUgyfel(datalist);break;
                case '\n':break;
                default: printf("A megadott opcio nem letezik. Nyomjon entert az ujra probalashoz.\n");getchar();getchar();
            }
        }
        system("clear");
    }while(choice!='0');
}
void ujUgyfel(ugyfel* root,char* datum){
    char* nev=malloc(sizeof(char)*26);
    char* email=malloc(sizeof(char)*26);
    char* telefonszam=malloc(sizeof(char)*26);
    char* kezdoosz=malloc(sizeof(char)*26);

    int run=1;
        while(run==1){
            system("clear");
            printf("Adja meg a fiok leendo azonositojat: ");
            scanf("%25s",nev);
            if(isPresent(root,nev)){
                printf("A megadott aznosito mar foglalt. Megprobalja ujra? (y/n)");
                getchar();
                if(getchar()=='n')
                    run=0;
            }else
                run=2;
        }
        while(run==2){
            system("clear");
            printf("Adja meg az ertesitesek fogadasara alkalmas e-mail cimet: ");
            scanf("%25s",email);
            if(!mailCheck(email)){
                printf("A megadott e-mail cim nem megfelelo. Megprobalja ujra? (y/n) ");
                getchar();
                if(getchar()=='n')
                    run=0;
            }else
                run=3;
        }
        while(run==3){
            system("clear");
            printf("Adjon meg egy elerhetosegre szolgalo telefonszamot ('+telszam' vagy 'telszam' formatumban): ");
            scanf("%25s",telefonszam);
            int res=telCheck(telefonszam);
            if(res!=1){
                switch(res){
                    case 0:printf("A megadott szam tul rovid. ");break;
                    case -1:printf("A megadott szam nem numerikus karaktert tartalmaz. ");break;
                }
                printf("Megprobalja ujra? (y/n) ");
                getchar();
                if(getchar()=='n')
                    run=0;
            }else
            run=4;
        }
        while(run==4){
            system("clear");
            printf("Mennyi penzt kotne le (barmi nem negativ szam)? ");
            scanf("%25s",kezdoosz);
            if(!isStringNumber(kezdoosz)){
                printf("A megadott osszeg nem egy megfelelo szam. Megprobalja ujra? (y/n) ");
                getchar();
                if(getchar()=='n')
                    run=0;
            }else
            run=5;
        }
    if(run==5){
        system("clear");
        addUgyfel(root,nev,email,telefonszam,kezdoosz,datum,"2");
        printf("Az uj ugyfel sikeresen felvetelre kerult. Nyomjon enter a folytatasert.");
        getchar();
        getchar();
    }
    free(nev);
    free(email);
    free(telefonszam);
    free(kezdoosz);
}

ugyfel* createElement(char* nev,char* email,char* telefonszam,char* kezdoosz,char* lasttrans,char* kamat){
    ugyfel* newElement=malloc(sizeof(ugyfel));
    char* _nev=malloc(sizeof(char)*26);
    char* _email=malloc(sizeof(char)*26);
    char* _telefonszam=malloc(sizeof(char)*26);
    char* _kezdoosz=malloc(sizeof(char)*26);
    char* _lasttrans=malloc(sizeof(char)*26);
    char* _kamat=malloc(sizeof(char)*26);
    if(!_nev||!_email||!_telefonszam||!_kezdoosz||!_lasttrans||!_kamat){
        printf("Hiba: nem sikerult memoriat lefoglalni. Netan gyenge a gep?");
        free(_nev);
        free(_email);
        free(_telefonszam);
        free(_kezdoosz);
        free(_lasttrans);
        free(_kamat);
        exit(1);
    }

    copyString(nev,_nev);
    copyString(email,_email);
    copyString(telefonszam,_telefonszam);
    copyString(kezdoosz,_kezdoosz);
    copyString(lasttrans,_lasttrans);
    copyString(kamat,_kamat);
    *newElement=(ugyfel){
        .name=_nev,
        .emailaddr=_email,
        .tel=_telefonszam,
        .funds=_kezdoosz,
        .date=_lasttrans,
        .intr=_kamat,
        .next=NULL
        };
    return newElement;
}
void addUgyfel(ugyfel* start,char* nev,char* email,char* telefonszam,char* kezdoosz,char* lasttrans,char* kamat){
    ugyfel* toAdd=createElement(nev, email,telefonszam, kezdoosz,lasttrans, kamat);
    ugyfel* current=start;
    while(current->next){
        current=current->next;
    }
    current->next=toAdd;
}
ugyfel* getUgyfelByNev(ugyfel* root, char* nev){
    ugyfel* current=root;
    while(!stringEquals(current->name,nev)){
        current=current->next;
    }
    return current;
}

void destroyList(ugyfel** start){
    ugyfel* toRemove;
    ugyfel* current=*start;
    while(current){
        toRemove=current;
        free(toRemove->name);
        free(toRemove->emailaddr);
        free(toRemove->tel);
        free(toRemove->funds);
        free(toRemove->date);
        free(toRemove->intr);
        current=current->next;
        free(toRemove);
    }
    *start=NULL;
}