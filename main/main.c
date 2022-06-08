#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct pdi *Listapdi;
typedef struct pdi{
	char nome[999];
	char horario[999];
	char descricao[999];
	int conta;
	Listapdi next;
}pdis;
typedef struct Local *Listalocais;
typedef struct Local{
	char local[999];
    int conta;
	Listapdi pdi;
	Listalocais next;
}locais;
typedef struct lnode *List;
typedef struct lnode {
    char nome[999];
    char morada[999];
    char data_nascimento[999];
    char telefone[999];
    char hot[999];
    Listalocais loc;
    Listapdi pis;
    List next;
} List_node;
List cria_listas (){
    List user = (List) malloc (sizeof (List_node));
    if (user != NULL) {
        user->next = NULL;
    }
    return user;
}
Listalocais cria_lista_local(){
    Listalocais local = (Listalocais) malloc(sizeof(locais));
    if (local != NULL){
        local->next = NULL;
    }
    return local;
}
Listapdi cria_lista_pdi(){
    Listapdi pdi = (Listapdi) malloc(sizeof(pdis));
    if (pdi != NULL){
        pdi->next = NULL;
    }
    return pdi;
}
void imprime_user(List user){
    List l=(List) malloc(sizeof(List_node));
    l=user;
    do{
        l=l->next;
        printf("nome: %s\n",l->nome);
        printf("morada: %s\n",l->morada);
        printf("data de nascimento: ");
        printf("%s\n",l->data_nascimento);
        printf("telefone: %s\n",l->telefone);
        printf("\n");
    }while (l->next != NULL);
}
void insere_lista (List user, char *key1, char *key2, char *key3, char *key4){
    List no = (List) malloc(sizeof(List_node));
    List ant = (List) malloc(sizeof(List_node));
    List atual = (List) malloc(sizeof(List_node));
    atual=user->next;
    ant=user;
    while (atual!=NULL){
        ant = atual;
        atual = atual->next;
    }
    strcpy(no->nome,key1);
    strcpy(no->morada,key2);
    strcpy(no->data_nascimento,key3);
    strcpy(no->telefone,key4);
    strcpy(no->hot,"");
    no->loc=cria_lista_local();
    no->pis=cria_lista_pdi();
    no->next = ant->next;
    ant->next = no;
}
void read_user (List user){
    List no = (List) malloc(sizeof(List_node));
    char string[999],aux[999];
    int i=0;
    int j=0;
    int u=0;
    FILE *f = fopen ("utilizadores.txt", "r");
    while ((fscanf (f, "%c", &string[i]))!= EOF){
        if ((string[i]!='-')&&(string[i]!='\n')){
            aux[j]=string[i];
            i++;
            j++;
        }
        else{
            aux[j]=0;
            u++;
            if (u==1){
                    strcpy(no->nome,aux);
            }
            if (u==2){
                    strcpy(no->morada,aux);
            }
            if (u==3){
                    strcpy(no->data_nascimento,aux);
            }
            if (u==4){
                    strcpy(no->telefone,aux);
                    insere_lista (user, no->nome, no->morada, no->data_nascimento, no->telefone);
                    u=0;
            }
            strcpy(aux,"");
            j=0;
            i++;
        }
    }
    fclose (f);
}
void procura_lista (List user, char nome[999], List *ant, List *atual){
    *ant = user; *atual = user->next;
    while (((*atual)!=NULL) && (strcmp((*atual)->nome,nome)!=0)){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}
void novo_user(List user){
    List no = (List) malloc(sizeof(List_node));
    List ant = (List) malloc(sizeof(List_node));
    List atual = (List) malloc(sizeof(List_node));
    printf("Qual o seu nome?\n");
    scanf("%s",&no->nome);
    procura_lista(user,no->nome,&ant,&atual);
    while((atual!=NULL)&&(strcmp(no->nome,"stop")!=0)){
        printf("Ja existe esse utilizador.\nEscreva o nome de um utilizador disponivel ou escreva 'stop'.\n");
        scanf("%s",&no->nome);
        procura_lista(user,no->nome,&ant,&atual);
    }
    if (atual==NULL){
        printf("Qual a sua morada?\n");
        scanf("%s",&no->morada);
        printf("Qual a sua data de nascimento?\n");
        scanf("%s",&no->data_nascimento);
        printf("Qual o seu telefone?\n");
        scanf("%s",&no->telefone);
        insere_lista (user, no->nome, no->morada, no->data_nascimento, no->telefone);
    }
}
void altera_user(List user){
    List no;
    List ant=(List) malloc(sizeof(List_node));
    List atual=(List) malloc(sizeof(List_node));
    char nome[999];
    printf("Qual o nome do utilizador que pretende alterar?\n");
    scanf("%s",&nome);
    procura_lista(user,nome,&ant,&atual);
    while((atual==NULL)&&(strcmp(nome,"stop")!=0)){
        printf("Nao existe esse utilizador.\nEscreva o nome de um utilizador existente ou escreva 'stop'.\n");
        scanf("%s",&nome);
        procura_lista(user,nome,&ant,&atual);
    }
    if (atual!=NULL){
        printf("Qual o novo nome?\n");
        scanf("%s",&atual->nome);
        printf("Qual a nova morada?\n");
        scanf("%s",&atual->morada);
        printf("Qual a nova data de nascimento?\n");
        scanf("%s",&atual->data_nascimento);
        printf("Qual o novo telefone?\n");
        scanf("%s",&atual->telefone);
    }
}
void imprime_pdi(Listapdi p){
    Listapdi l=(Listapdi) malloc(sizeof(pdis));
    l=p;
    printf("Pontos de interesse:\n");
    do{
        l=l->next;
        printf("%s-",l->nome);
        printf("%s-",l->horario);
        printf("%s",l->descricao);
        printf("\n");
    }while (l->next != NULL);
}
void imprime_local(Listalocais local){
    Listalocais l=(Listalocais) malloc(sizeof(locais));
    l=local;
    do{
        l=l->next;
        printf("local: %s\n",l->local);
        imprime_pdi(l->pdi);
    }while (l->next != NULL);
}
void insere_pdi(Listapdi pdi, char *key1, char *key2, char *key3){
    Listapdi no = (Listapdi) malloc(sizeof(pdis));
    Listapdi ant = (Listapdi) malloc(sizeof(pdis));
    Listapdi atual = (Listapdi) malloc(sizeof(pdis));
    atual=pdi->next;
    ant=pdi;
    while ((atual!=NULL) && (strcmp(atual->nome,key1)==-1)){
        ant = atual;
        atual = atual->next;
    }
    strcpy(no->nome,key1);
    strcpy(no->horario,key2);
    strcpy(no->descricao,key3);
    no->conta=0;
    no->next = ant->next;
    ant->next = no;
}
void insere_local(Listalocais local, char *key, Listapdi p){
    Listalocais no = (Listalocais) malloc(sizeof(locais));
    Listapdi pdi = cria_lista_pdi();
    Listalocais ant;
    Listalocais atual;
    atual=local->next;
    ant=local;
    while ((atual!=NULL) && (strcmp(atual->local,key)==-1)){
        ant = atual;
        atual = atual->next;
    }
    strcpy(no->local,key);
    no->conta=0;
    no->pdi=p;
    no->next = ant->next;
    ant->next = no;
}
void read_local (Listalocais local,Listapdi pdi){
    Listalocais no_l = (Listalocais) malloc(sizeof(locais));
    Listapdi no_pdi = (Listapdi) malloc(sizeof(pdis));
    Listapdi p = (Listapdi) malloc(sizeof(pdis));
    char string[5000],aux[999];
    int i=0;
    int j=0;
    int u=0;
    FILE *f = fopen ("locais.txt", "r");
    while ((fscanf (f, "%c", &string[i]))!= EOF){
        if ((string[i]!='-')&&(string[i]!=';')&&(string[i]!='|')&&(string[i]!='\n')){
            aux[j]=string[i];
            i++;
            j++;
        }
        else if (string[i]==';'){
            u=0;
            insere_local(local, no_l->local, p);
            p=cria_lista_pdi();
            i++;
        }
        else if ((string[i]=='-')||(string[i]==';')||(string[i]=='|')){
            aux[j]=0;
            u++;
            if (u==1){
                    strcpy(no_l->local,aux);
            }
            if (u==2){
                    strcpy(no_pdi->nome,aux);
            }
            if (u==3){
                    strcpy(no_pdi->horario,aux);
            }
            if (u==4){
                    strcpy(no_pdi->descricao,aux);
                    insere_pdi(p, no_pdi->nome, no_pdi->horario, no_pdi->descricao);
                    insere_pdi(pdi, no_pdi->nome, no_pdi->horario, no_pdi->descricao);
                    u=1;
            }
            strcpy(aux,"");
            j=0;
            i++;
        }
    }
    fclose (f);
}
void procura_local (Listalocais local, char nome[999], Listalocais *ant, Listalocais *atual){
    *ant = local; *atual = local->next;
    while (((*atual)!=NULL) && (strcmp((*atual)->local,nome)!=0)){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}
void procura_pdi (Listapdi pdi, char nome[999], Listapdi *ant, Listapdi *atual){
    *ant = pdi; *atual = pdi->next;
    while (((*atual)!=NULL)&&(strcmp((*atual)->nome,nome)!=0)){
        *ant = *atual;
        *atual = (*atual)->next;
    }
}
void procura_pdi2 (Listalocais pdi, char nome[999], Listalocais *ant, Listalocais *atual, Listapdi *atual_p){
    Listapdi ant_p;
    *ant = pdi; *atual = pdi->next;
    while (((*atual)!=NULL)){
        ant_p = (*atual)->pdi;
        *atual_p = ant_p->next;
        while (((*atual_p)!=NULL)&&(strcmp((*atual_p)->nome,nome)!=0)){
            ant_p = *atual_p;
            *atual_p = (*atual_p)->next;
        }
        if ((*atual_p)!=NULL){
            break;
        }
        else{
            *ant = *atual;
            *atual = (*atual)->next;
        }
    }
}
void insere_user_pdi(Listapdi pdi,char *key){
    Listapdi no = (Listapdi) malloc(sizeof(pdis));
    Listapdi ant;
    Listapdi atual;
    atual=pdi->next;
    ant=pdi;
    while ((atual!=NULL) && (strcmp(atual->nome,key)==-1)){
        ant = atual;
        atual = atual->next;
    }
    strcpy(no->nome,key);
    no->next = ant->next;
    ant->next = no;
}
void insere_user_local(Listalocais local,char *key){
    Listalocais no = (Listalocais) malloc(sizeof(locais));
    Listalocais ant;
    Listalocais atual;
    atual=local->next;
    ant=local;
    int q;
    for (q=0;q<3;q++){
        if ((atual!=NULL) && (strcmp(atual->local,key)<0)){
            ant = atual;
            atual = atual->next;
        }
        else
            break;
    }
    strcpy(no->local,key);
    no->next = ant->next;
    ant->next = no;
    atual = local->next;
    ant = local;
    q=0;
    while(atual!=NULL){
        q++;
        if(q<=3){
            ant = ant->next;
            atual = atual->next;
        }
        else{
            ant->next = atual->next;
            free(atual);
            atual = ant->next;
        }

    }
}
void imprime_user_local(Listalocais locais){
    Listalocais l=(Listalocais) malloc(sizeof(locais));
    l=locais;
    do{
        l=l->next;
        printf("%s\n",l->local);
    }while (l->next != NULL);
}
void imprime_user_pdi(Listapdi p){
    Listapdi l=(Listapdi) malloc(sizeof(pdis));
    l=p;
    do{
        l=l->next;
        printf("%s\n",l->nome);
    }while (l->next != NULL);
}
void remove_user_local(Listalocais local, char *key){
    Listalocais no = (Listalocais) malloc(sizeof(locais));
    Listalocais ant;
    Listalocais atual;
    atual=local->next;
    ant=local;
    int q;
    while ((atual!=NULL) && (strcmp(atual->local,key)==-1)){
        ant = atual;
        atual = atual->next;
    }
    atual = atual->next;
    ant->next = atual;
}
void remove_user_pdi(Listapdi pdi,char *key){
    Listapdi no = (Listapdi) malloc(sizeof(pdis));
    Listapdi ant;
    Listapdi atual;
    atual=pdi->next;
    ant=pdi;
    while ((atual!=NULL) && (strcmp(atual->nome,key)==-1)){
        ant = atual;
        atual = atual->next;
    }
    atual = atual->next;
    ant->next = atual;
}
void adiciona_locais_pdis(List user, Listalocais local, Listapdi pdi){
    int s;
    List ant=(List) malloc(sizeof(List_node));
    List atual=(List) malloc(sizeof(List_node));
    Listalocais ant_local=(Listalocais) malloc(sizeof(locais));
    Listalocais atual_local=(Listalocais) malloc(sizeof(locais));
    Listapdi ant_pdi=(Listapdi) malloc(sizeof(pdis));
    Listapdi atual_pdi=(Listapdi) malloc(sizeof(pdis));
    Listalocais no_l = (Listalocais) malloc(sizeof(locais));
    Listapdi no_p = (Listapdi) malloc(sizeof(pdis));
    no_l=user->loc;
    no_p=user->pis;
    char nome[999];
    char loc[999];
    char p[999];
    printf("Qual o seu nome de utilizador?\n");
    scanf("%s",&nome);
    procura_lista(user,nome,&ant,&atual);
    while((atual==NULL)&&(strcmp(nome,"stop")!=0)){
        printf("Nao existe esse utilizador.\nEscreva o nome de um utilizador existente ou escreva 'stop'.\n");
        scanf("%s",&nome);
        procura_lista(user,nome,&ant,&atual);
    }
    if (atual!=NULL){
        printf("Lembre-se se ja tiver 3 locais como preferidos nada sera adicionado.\n");
        printf("Se pretende adicionar local selecione 1.\n");
        printf("Se pretende adicionar ponto de interesse selecione 2.\n");
        printf("Se pretende adicionar ponto de interesse hot selecione 3.\n");
        printf("Se pretende sair selecione qualquer outro numero.\n");
        scanf("%d",&s);
        if (s==1){
            printf("Qual o local que pretende adicionar?\n");
            scanf("%s",&loc);
            procura_local(local,loc,&ant_local,&atual_local);
            while((atual_local==NULL)&&(strcmp(loc,"stop")!=0)){
                printf("Nao existe esse local.\nEscreva o nome de um local existente ou escreva 'stop'.\n");
                scanf("%s",&loc);
                procura_local(local,loc,&ant_local,&atual_local);
            }
            if (atual_local!=NULL){
                no_l=atual->loc;
                procura_local(no_l,loc,&ant_local,&atual_local);
                if (atual_local==NULL){
                    procura_local(local,loc,&ant_local,&atual_local);
                    atual_local->conta++;
                    insere_user_local(no_l,loc);
                    printf("Locais preferidos:\n");
                    imprime_user_local(no_l);
                }
            }
        }
        if (s==2){
            printf("Qual o ponto de interesse que pretende adicionar?\n");
            scanf("%s",&p);
            procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
            while((atual_pdi==NULL)&&(strcmp(p,"stop")!=0)){
                printf("Nao existe esse ponto de interesse.\nEscreva o nome de um ponto de interess existente ou escreva 'stop'.\n");
                scanf("%s",&p);
                procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
            }
            if (atual_pdi!=NULL){
                no_p=atual->pis;
                procura_pdi(no_p,p,&ant_pdi,&atual_pdi);
                if (atual_pdi==NULL){
                    procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
                    atual_pdi->conta++;
                    insere_user_pdi(no_p,p);
                    printf("pdis preferidos:\n");
                    imprime_user_pdi(no_p);
                }
            }
        }
        if (s==3){
            printf("Se tiver um pdi hot ja guardado ira substituir pelo atual.\nSe pretende prosseguir escreva 3 novamente.\n");
            scanf("%s",&s);
            if (s==3){
                printf("Qual o ponto de interesse hot que pretende selecionar?\n");
                scanf("%s",&p);
                procura_pdi(pdi,p,&ant_pdi,&atual_pdi);
                while((atual_pdi==NULL)&&(strcmp(p,"stop")!=0)){
                    printf("Nao existe esse ponto de interesse.\nEscreva o nome de um ponto de interess existente ou escreva 'stop'.\n");
                    scanf("%s",&p);
                    procura_pdi(pdi,p,&ant_pdi,&atual_pdi);
                }
                strcpy(atual->hot,p);
            }
        }
    }
}
void remove_locais_pdis(List user, Listalocais local, Listapdi pdi){
    int s;
    List ant=(List) malloc(sizeof(List_node));
    List atual=(List) malloc(sizeof(List_node));
    Listalocais ant_local=(Listalocais) malloc(sizeof(locais));
    Listalocais atual_local=(Listalocais) malloc(sizeof(locais));
    Listapdi ant_pdi=(Listapdi) malloc(sizeof(pdis));
    Listapdi atual_pdi=(Listapdi) malloc(sizeof(pdis));
    Listalocais no_l = (Listalocais) malloc(sizeof(locais));
    Listapdi no_p = (Listapdi) malloc(sizeof(pdis));
    no_l=user->loc;
    no_p=user->pis;
    char nome[999];
    char loc[999];
    char p[999];
    printf("Qual o seu nome de utilizador?\n");
    scanf("%s",&nome);
    procura_lista(user,nome,&ant,&atual);
    while((atual==NULL)&&(strcmp(nome,"stop")!=0)){
        printf("Nao existe esse utilizador.\nEscreva o nome de um utilizador existente ou escreva 'stop'.\n");
        scanf("%s",&nome);
        procura_lista(user,nome,&ant,&atual);
    }
    if (atual!=NULL){
        printf("Se pretende remover local selecione 1.\n");
        printf("Se pretende remover ponto de interesse selecione 2.\n");
        printf("Se pretende remover ponto de interesse hot selecione 3.\n");
        printf("Se pretende sair selecione qualquer outro numero.\n");
        scanf("%d",&s);
        if (s==1){
            printf("Qual o local que pretende remover?\n");
            scanf("%s",&loc);
            procura_local(local,loc,&ant_local,&atual_local);
            while((atual_local==NULL)&&(strcmp(loc,"stop")!=0)){
                printf("Nao existe esse local.\nEscreva o nome de um local existente ou escreva 'stop'.\n");
                scanf("%s",&loc);
                procura_local(local,loc,&ant_local,&atual_local);
            }
            if (atual_local!=NULL){
                no_l=atual->loc;
                procura_local(no_l,loc,&ant_local,&atual_local);
                if (atual_local!=NULL){
                    procura_local(local,loc,&ant_local,&atual_local);
                    atual_local->conta--;
                    remove_user_local(no_l,loc);
                    printf("Locais preferidos:\n");
                    imprime_user_local(no_l);
                }
            }
        }
        if (s==2){
            printf("Qual o ponto de interesse que pretende remover?\n");
            scanf("%s",&p);
            procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
            while((atual_pdi==NULL)&&(strcmp(p,"stop")!=0)){
                printf("Nao existe esse ponto de interesse.\nEscreva o nome de um ponto de interess existente ou escreva 'stop'.\n");
                scanf("%s",&p);
                procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
            }
            if (atual_pdi!=NULL){
                no_p=atual->pis;
                procura_pdi(no_p,p,&ant_pdi,&atual_pdi);
                if (atual_pdi!=NULL){
                    procura_pdi2(local,p,&ant_local,&atual_local,&atual_pdi);
                    atual_pdi->conta--;
                    remove_user_pdi(no_p,p);
                    printf("pdis preferidos:\n");
                    imprime_user_pdi(no_p);
                }
            }
        }
        if (s==3){
            strcpy(atual->hot,"");
            printf("O pdi hot foi removido com sucesso.");
        }
    }
}
void read_pref(List user,Listalocais local){
    List ant=(List) malloc(sizeof(List_node));
    List atual=(List) malloc(sizeof(List_node));
    Listalocais ant_local=(Listalocais) malloc(sizeof(locais));
    Listalocais atual_local=(Listalocais) malloc(sizeof(locais));
    Listalocais ant_pdi=(Listalocais) malloc(sizeof(locais));
    Listalocais atual_pdi=(Listalocais) malloc(sizeof(locais));
    Listalocais no_l = (Listalocais) malloc(sizeof(locais));
    Listapdi no_p = (Listapdi) malloc(sizeof(pdis));
    Listapdi p,ant_pdi2;
    no_l=user->loc;
    no_p=user->pis;
    char string[999],aux[999],aux_nome[999];
    int i=0;
    int j=0;
    int u=0;
    FILE *f = fopen ("preferencias.txt", "r");
    while ((fscanf (f, "%c", &string[i]))!= EOF){
        if (string[i]!='\n'){
            aux[j]=string[i];
            i++;
            j++;
        }
        else{
            aux[j]=0;

            procura_lista(user,aux,&ant,&atual);
            procura_local(local,aux,&ant_local,&atual_local);
            procura_pdi2(local,aux,&ant_pdi,&atual_pdi,&p);
            if (atual!=NULL){
                strcpy(aux_nome,aux);
            }
            if (atual==NULL){
                procura_lista(user,aux_nome,&ant,&atual);
            }
            if ((atual_local!=NULL)&&(strcmp(atual_local->local,aux)==0)){
                no_l=atual->loc;
                procura_local(no_l,aux,&ant_local,&atual_local);
                if (atual_local==NULL){
                    procura_local(local,aux,&ant_local,&atual_local);
                    atual_local->conta++;
                    insere_user_local(no_l,aux);
                }
            }
            if (p!=NULL){
                no_p=atual->pis;
                procura_pdi(no_p,aux,&ant_pdi2,&p);
                if (p==NULL){
                    procura_pdi2(local,aux,&ant_pdi,&atual_pdi,&p);
                    p->conta++;
                    insere_user_pdi(atual->pis,aux);
                }
            }
            strcpy(aux,"");
            j=0;
            i++;
        }
    }
    fclose (f);
}
void guarda_user(List user){
    List l=(List) malloc(sizeof(List_node));
    l=user;
    FILE *f = fopen ("utilizadores.txt", "w");
    do{
        l=l->next;
        fprintf(f,"%s-",l->nome);
        fprintf(f,"%s-",l->morada);
        fprintf(f,"%s-",l->data_nascimento);
        fprintf(f,"%s",l->telefone);
        fprintf(f,"\n");
    }while (l->next != NULL);
    fclose(f);
}
void procura_lista_new_pdi(Listapdi lista, Listapdi chave, Listapdi *ant, Listapdi *actual) {
    *ant = lista;
    *actual = lista->next;
    while(((*actual)!=NULL) && (((*actual)->conta) >= (chave->conta))) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
}
void insere_lista_new_pdi(Listapdi lista, Listapdi varPDI) {
    Listapdi no = (Listapdi) malloc(sizeof(pdis));
    if (no!=NULL) {
        Listapdi ant, inutil;
        strcpy(no->nome,varPDI->nome);
        strcpy(no->horario,varPDI->horario);
        strcpy(no->descricao,varPDI->descricao);
        no->conta=varPDI->conta;
        procura_lista_new_pdi(lista, varPDI, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void procura_lista_new_cid(Listalocais lista, Listalocais chave, Listalocais *ant, Listalocais *actual) {
    *ant = lista;
    *actual = lista->next;
    while(((*actual)!=NULL) && (((*actual)->conta) >= (chave->conta))) {
        *ant=*actual;
        *actual=(*actual)->next;
    }
}
void insere_lista_new_cid(Listalocais lista, Listalocais varCID, Listapdi varPDI) {
    Listalocais no = (Listalocais) malloc(sizeof(locais));
    if (no!=NULL) {
        Listalocais ant, inutil;
        strcpy(no->local,varCID->local);
        no->conta=varCID->conta;
        no->pdi=varPDI;
        procura_lista_new_cid(lista, varCID, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}
void ordena_loc(Listalocais local, Listalocais local2){
    Listalocais aux = local->next;
    Listapdi aux2;
    Listapdi aux3;
    while (aux!=NULL){
        aux2 = aux->pdi;
        aux2 = aux2->next;
        aux3 = cria_lista_pdi();
        while (aux2!=NULL){
            insere_lista_new_pdi(aux3, aux2);
            aux2=aux2->next;
        }
        insere_lista_new_cid(local2,aux,aux3);
        aux = aux->next;
    }
}
void procura_local2(List user,Listalocais local,Listalocais *ant,Listalocais *atual, char loc[999], char loc1[999]){
    *ant = local; *atual = local->next;
    Listalocais ant2, atual2;
    while ((*atual)!=NULL){
        ant2=user->loc;
        atual2=ant2->next;
        while ((atual2 != NULL)&&((strcmp((*atual)->local,atual2->local)!=0))){
            ant2 = atual2;
            atual2 = atual2->next;
        }
        if (strcmp(loc,atual2->local)==0){
            ant2 = atual2;
            atual2 = atual2->next;
            while ((atual2 != NULL)&&((strcmp((*atual)->local,atual2->local)!=0))){
                ant2 = atual2;
                atual2 = atual2->next;
            }
        }
        else if (strcmp(loc1,atual2->local)==0){
            ant2 = atual2;
            atual2 = atual2->next;
            while ((atual2 != NULL)&&((strcmp((*atual)->local,atual2->local)!=0))){
                ant2 = atual2;
                atual2 = atual2->next;
            }
        }
        if (atual2==NULL){
            *ant = *atual;
            *atual = (*atual)->next;
        }
        else{
            break;
        }
    }
}
void procura_pdi3(List user,Listapdi pdi,Listapdi *ant,Listapdi *atual, char p[999], char p1[999]){
    *ant = pdi; *atual = pdi->next;
    Listapdi ant2, atual2;
    while ((*atual)!=NULL){
        ant2=user->pis;
        atual2=ant2->next;
        while ((atual2 != NULL)&&((strcmp((*atual)->nome,atual2->nome)!=0))){
            ant2 = atual2;
            atual2 = atual2->next;
        }
        if (atual2 != NULL){
            if ((strcmp(p,atual2->nome)==0)&&(atual2 != NULL)){
                ant2 = atual2;
                atual2 = atual2->next;
                while ((atual2 != NULL)&&((strcmp((*atual)->nome,atual2->nome)!=0))){
                    ant2 = atual2;
                    atual2 = atual2->next;
                }
            }
            else if ((strcmp(p1,atual2->nome)==0)&&(atual2 != NULL)){
                ant2 = atual2;
                atual2 = atual2->next;
                while ((atual2 != NULL)&&((strcmp((*atual)->nome,atual2->nome)!=0))){
                    ant2 = atual2;
                    atual2 = atual2->next;
                }
            }
        }
        if (atual2==NULL){
            *ant = *atual;
            *atual = (*atual)->next;
        }
        else{
            break;
        }
    }
}
void procura_pdi4(Listapdi pdi,Listapdi *ant,Listapdi *atual, char p[999], char p1[999]){
    *ant = pdi; *atual = pdi->next;
    //printf("%s\n",(*atual)->nome);
    if (strcmp((*atual)->nome,p)==0){
        *ant = *atual;
        *atual = (*atual)->next;
    }
    //printf("%s\n",(*atual)->nome);
    if (strcmp((*atual)->nome,p1)==0){
        *ant = *atual;
        *atual = (*atual)->next;
        if (strcmp((*atual)->nome,p)==0){
            *ant = *atual;
            *atual = (*atual)->next;
        }
    }
    //printf("%s\n",(*atual)->nome);
}
double n_user(List user){
    List ant,atual;
    ant=user;atual=user->next;
    double c=0;
    while (atual!=NULL){
        ant=atual;
        atual=atual->next;
        c++;
    }
    return c;
}
double n_loc_p(List user,char loc[999],char loc1[999],char loc2[999]){
    List ant,atual;
    Listalocais ant_l,atual_l;
    ant=user;atual=user->next;
    int d=0;
    while (atual!=NULL){
        ant_l=atual->loc;
        atual_l=ant_l->next;
        while (atual_l!=NULL){
            if ((strcmp(atual_l->local,loc)==0)||(strcmp(atual_l->local,loc1)==0)||(strcmp(atual_l->local,loc2)==0)){
                d++;
                break;
            }
            ant_l=atual_l;
            atual_l=atual_l->next;
        }
        ant=atual;
        atual=atual->next;
    }
    return d;
}
void n_hot(List user,char p[999],char p1[999],char p2[999],double *conta){
    List ant,atual;
    ant=user;atual=user->next;
    while (atual!=NULL){
        if ((strcmp(atual->hot,p)==0)||(strcmp(atual->hot,p1)==0)||(strcmp(atual->hot,p2)==0)){
            (*conta)++;
        }
        ant=atual;
        atual=atual->next;
    }
}
void n_pdi_p(List user,char p[999],char p1[999],char p2[999],double *conta){
    Listapdi ant,atual;
    ant=user->pis;
    atual=ant->next;
    while (atual!=NULL){
        if ((strcmp(atual->nome,p)==0)||(strcmp(atual->nome,p1)==0)||(strcmp(atual->nome,p2)==0)){
            (*conta)++;
        }
        ant=atual;
        atual=atual->next;
    }
}
void n_pdi_p_total(List user,double *conta){
    Listapdi ant,atual;
    ant=user->pis;
    atual=ant->next;
    while (atual!=NULL){
        (*conta)++;
        ant=atual;
        atual=atual->next;
    }
}
void imprime_viagem(Listalocais local, List user){
    List no;
    List ant=(List) malloc(sizeof(List_node));
    List atual=(List) malloc(sizeof(List_node));
    Listalocais atual_local=(Listalocais) malloc(sizeof(locais));
    Listalocais ant_local2=(Listalocais) malloc(sizeof(locais));
    Listalocais atual_local2=(Listalocais) malloc(sizeof(locais));
    Listapdi ant_pdi=(Listapdi) malloc(sizeof(pdis));
    Listapdi atual_pdi=(Listapdi) malloc(sizeof(pdis));
    Listapdi n;
    int i,j,a,b;
    double loc_f,hot_f,c,d,conta,conta_pdi,pdi_f,conta_pdi_total;
    d=0;
    conta=0;
    conta_pdi=0;
    conta_pdi_total=0;
    c=n_user(user);
    a=0;
    b=0;
    char nome[999],loc[999],loc1[999],loc2[999],p[999],p1[999],p2[999],hot[999];
    strcpy(loc,"");
    strcpy(loc1,"");
    strcpy(p,"");
    strcpy(p1,"");
    printf("Qual o seu nome de utilizador?\n");
    scanf("%s",&nome);
    procura_lista(user,nome,&ant,&atual);
    while((atual==NULL)&&(strcmp(nome,"stop")!=0)){
        printf("Nao existe esse utilizador.\nEscreva o nome de um utilizador existente ou escreva 'stop'.\n");
        scanf("%s",&nome);
        procura_lista(user,nome,&ant,&atual);
    }
    atual_local=atual->loc;
    atual_local=atual_local->next;
    if (atual_local!=NULL){
        atual_local=atual_local->next;
        if (atual_local!=NULL){
            atual_local=atual_local->next;
            if (atual_local!=NULL){
                for (i=0;i<3;i++){
                    procura_local2(atual,local,&ant_local2,&atual_local2,loc,loc1);
                    printf("local: ");
                    if (a==0){
                        strcpy(loc,atual_local2->local);
                        printf("%s\n",loc);
                    }
                    if (a==1){
                        strcpy(loc1,atual_local2->local);
                        printf("%s\n",loc1);
                    }
                    if (a==2){
                        strcpy(loc2,atual_local2->local);
                        printf("%s\n",loc2);
                    }
                    a++;
                    for (j=0;j<3;j++){
                        printf("Ponto de interesse: ");
                        strcpy(hot,atual->hot);
                        procura_pdi(atual_local2->pdi,hot,&ant_pdi,&atual_pdi);
                        if ((atual_pdi!=NULL)&&(b==0)){
                                strcpy(p,atual_pdi->nome);
                                printf("%s\n",p);
                        }
                        else{
                            procura_pdi3(atual,atual_local2->pdi,&ant_pdi,&atual_pdi,p,p1);
                            if (atual_pdi!=NULL){
                                if (b==0){
                                    strcpy(p,atual_pdi->nome);
                                    printf("%s\n",p);
                                }
                                if (b==1){
                                    strcpy(p1,atual_pdi->nome);
                                    printf("%s\n",p1);
                                }
                                if (b==2){
                                    strcpy(p2,atual_pdi->nome);
                                    printf("%s\n",p2);
                                }
                            }
                            else {
                                procura_pdi4(atual_local2->pdi,&ant_pdi,&atual_pdi,p,p1);
                                if (b==0){
                                    strcpy(p,atual_pdi->nome);
                                    printf("%s\n",p);
                                }
                                if (b==1){
                                    strcpy(p1,atual_pdi->nome);
                                    printf("%s\n",p1);
                                }
                                if (b==2){
                                    strcpy(p2,atual_pdi->nome);
                                    printf("%s\n",p2);
                                }
                            }
                        }
                        b++;
                    }
                    n_hot(user,p,p1,p2,&conta);
                    n_pdi_p(atual,p,p1,p2,&conta_pdi);
                    b=0;
                }
                n_pdi_p_total(atual,&conta_pdi_total);
                d=n_loc_p(user,loc,loc1,loc2);
                loc_f=d/c*100;
                hot_f=conta/c*100;
                pdi_f=conta_pdi/conta_pdi_total*100;
                printf("Percentagem de utilizadores com pelo menos um destes locais com preferidos:\n");
                printf("%.2lf\n",loc_f);
                printf("Percentagem de utilizadores com o ponto de interesse hot na viagem:\n");
                printf("%.2lf\n",hot_f);
                printf("Percentagem das preferencias de PDI:\n");
                printf("%.2lf\n",pdi_f);
            }
            else{
                printf("Ainda nao tem 3 locais preferidos.\n");
            }
        }
        else{
            printf("Ainda nao tem 3 locais preferidos.\n");
        }
    }
    else{
        printf("Ainda nao tem 3 locais preferidos.\n");
    }
}
void guarda_pref(List user){
    List l=(List) malloc(sizeof(List_node));
    Listalocais ll;
    Listapdi lp;
    l=user;
    FILE *f = fopen ("preferencias.txt", "w");
    do{
        l=l->next;
        fprintf(f,"%s",l->nome);
        fprintf(f,"\n");
        ll=l->loc;
        ll=ll->next;
        while (ll != NULL){
            fprintf(f,"%s",ll->local);
            fprintf(f,"\n");
            ll=ll->next;
        }
        lp = l->pis;
        lp = lp->next;
        while (lp != NULL){
            fprintf(f,"%s",lp->nome);
            fprintf(f,"\n");
            lp = lp->next;
        }
    }while (l->next != NULL);
    fclose (f);
}
void imprime_pref(List user){
    List l=(List) malloc(sizeof(List_node));
    Listalocais ll;
    Listapdi lp;
    l=user;
    do{
        l=l->next;
        printf("%s",l->nome);
        printf("\n");
        ll=l->loc;
        ll=ll->next;
        while (ll != NULL){
            printf("%s",ll->local);
            printf("\n");
            ll=ll->next;
        }
        lp = l->pis;
        lp = lp->next;
        while (lp != NULL){
            printf("%s",lp->nome);
            printf("\n");
            lp = lp->next;
        }
    }while (l->next != NULL);
}
void read_hot(List user, Listapdi pdi){
    Listapdi ant_pdi,atual_pdi;
    int i,j;
    char aux[999],string[999],aux_nome[999];
    List ant,atual;
    FILE *f = fopen ("hot.txt", "r");
    while ((fscanf (f, "%c", &string[i]))!= EOF){
        if (string[i]!='\n'){
            aux[j]=string[i];
            i++;
            j++;
        }
        else{
            aux[j]=0;
            procura_lista(user,aux,&ant,&atual);
            procura_pdi(pdi,aux,&ant_pdi,&atual_pdi);
            if (atual!=NULL){
                strcpy(aux_nome,aux);
            }
            if (atual==NULL){
                procura_lista(user,aux_nome,&ant,&atual);
            }
            if (atual_pdi!=NULL){
                strcpy(atual->hot,aux);
            }
            strcpy(aux,"");
            j=0;
            i++;
        }
    }
    fclose (f);
}
void guarda_hot(List user){
    List l=(List) malloc(sizeof(List_node));
    l=user;
    FILE *f = fopen ("hot.txt", "w");
    do{
        l=l->next;
        fprintf(f,"%s",l->nome);
        fprintf(f,"\n");
        if (strcmp(l->hot,"")!=0){
            fprintf(f,"%s",l->hot);
            fprintf(f,"\n");
        }
    }while (l->next != NULL);
    fclose (f);
}
int main(){
    List user = cria_listas ();
    Listalocais local = cria_lista_local();
    Listapdi pdi = cria_lista_pdi();
    Listalocais local2 = cria_lista_local();
    Listapdi pdi2 = cria_lista_pdi();
    read_user(user);
    read_local (local,pdi);
    read_pref(user,local);
    ordena_loc(local,local2);
    read_hot(user,pdi);
    int opcao,opcao2;
    do{
        printf("___________________MENU___________________\n");
        printf("|Selecione a opcao que pretende          |\n");
        printf("|1.Adicionar novo utilizador             |\n");
        printf("|2.Alterar utilizador ja existente       |\n");
        printf("|3.Mostrar utilizadores ja existentes    |\n");
        printf("|4.Mostrar locais seguidos dos seus pdis |\n"); /*depois aparece 2 opcoes.  Uma ordem alfabetica outra por popularidade*/
        printf("|5.Mostrar locais disponiveis            |\n");
        printf("|6.Mostrar pdis disponiveis              |\n");
        printf("|7.Adicionar locais e pdis de preferencia|\n");
        printf("|8.Remover locais e pdis de preferencia  |\n");
        printf("|9.Fazer plano de viagem                 |\n");
        printf("|10.Sair                                 |\n");
        printf("|Qualquer outro numero volta a este menu |\n");
        printf("|________________________________________|\n");
        scanf("%d",&opcao);
        if (opcao==1){
            novo_user(user);
        }
        else if (opcao==2){
            altera_user(user);
        }
        else if (opcao==3){
            imprime_user(user);
        }
        else if (opcao==4){
            do{
                printf("___________________MENU___________________\n");
                printf("|Selecione a opcao que pretende          |\n");
                printf("|1.Por ordem alfabetica                  |\n");
                printf("|2.Por ordem de popularidade             |\n");
                printf("|3.Sair                                  |\n");
                printf("|Qualquer outro numero volta a este menu |\n");
                printf("|________________________________________|\n");
                scanf("%d",&opcao2);
                if (opcao2==1){
                    imprime_local(local);
                }
                else if (opcao2==2){
                    imprime_local(local2);
                }
            }while (opcao2!=3);
        }
        else if (opcao==5){
            imprime_user_local(local);
        }
        else if (opcao==6){
            imprime_user_pdi(pdi);
        }
        else if (opcao==7){
            adiciona_locais_pdis(user,local,pdi);
            local2 = cria_lista_local();
            ordena_loc(local,local2);
        }
        else if (opcao==8){
            remove_locais_pdis(user,local,pdi);
            local2 = cria_lista_local();
            ordena_loc(local,local2);
        }
        else if (opcao==9){
            imprime_viagem(local2,user);
        }
    }while (opcao!=10);
    guarda_user(user);
    guarda_pref(user);
    guarda_hot(user);
}
