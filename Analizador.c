/*
*		Descripción de la Tarea:
*		Implementar un analizador sintáctico (descendente recursivo o LL(1))
*		para reconocer un fuente en un lenguaje matemático. Se trabajará
*		con números reales y arrays unidimensionales, más estructuras de
*		control repetitivas y condicionales. Más abajo se muestran ejemplos
*		de fuentes que deberían ser reconocidos. Se debe, además, proponer
*		el BNF de las reglas gramaticales que serán reconocidas. Se debería
*		re-utilizar el analizador léxico implementado en la tarea 1 si se
*		dispone del mismo, caso contrario tendrá que implementarlo. En caso
*		de errores sintácticos se otorgará una mejor evaluación a aquellos
*		trabajos que implementen una estrategia de manejo de errores
*		basado en sincronización de tokens y que permita continuar el
*		parsing.
*		Alumno: FAbio Lara        
*/

/*********** LIbrerias utilizadas **************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/***************** MACROS **********************/
//Codigos
#define PROGRAMA    300
#define HEADER      301
#define LISTA_SENT  302
#define HEADER2     303
#define DECLARACION 304
#define LISTAVAR    305
#define LISTAVAR2   306
#define LISTA_SENT2 307
#define SENTENCIA   308
#define S_WRITE     309
#define S_WRITELN   310
#define S_FOR       311
#define S_IF        312
#define ASIGNACION  313
#define IMPRIMIBLE  314
#define LITERAL     315
#define EXP         316
#define TERM        317
#define FACTOR      318
#define EXP2        319
#define TER2        320
#define ADDOP       321
#define MULOP       322
#define ID          323
#define BOOLEAN     324
#define RECUPERACION 325
#define FIN         326
#define SIGNO       327
#define ELSE        328
#define TOKENS_IGUALES    329
#define ERROR     999
#define TAMLEX 		31
// Fin Codigos
#define TRUE 1
#define FALSE 0

/************* Definiciones ********************/
typedef struct{
    char valor_token[TAMLEX];
    int num_linea;
} token;

token pila_de_tokens[1000];
                           
FILE *archivo;		
int pos_pila=0;
    
int main(int cantArg, char *arg[]){
    system("cls");
    if(cantArg>1){
          if(!(archivo=fopen(fopen(args[1],"rt"))){
            printf("No existe archivo especificado!\n\n");
            }
            else{
                printf("-----ERRORES LEXICOS-----\n\n");
                sgteLex();
                strcpy(pila_de_tokens[pos_pila].valor_token,"$");
                
                if(pos_pila>1){
                     printf("\n\n\n\n--------ERRORES SINTACTICOS--------\n\n");
                    analizador_sintactico(pila_de_tokens,pos_pila);
                    }
                    else
                        printf("Se esperaba sentencia(s)\n\n");
                }    
       }
       else{
            printf("No se especifico archivo fuente!\n\n");*/
           }
       printf("Programa terminado!\n\n");
    return 0;
    }


int  sgteLex(){
    char elemento[TAMLEX];		
    int num_linea=1;			
    char msg[300];
	char caracter;
	int acepto;
	int estado;
    int error;
    
	while((caracter=fgetc(archivo))!=EOF){
        int i=0, longid=0;
		error=0;
		if (caracter==' ' || caracter=='\t')
			continue;	
		else if(caracter=='\n'){
			num_linea++;
			continue;
		}
		else if (isalpha(caracter)){
			i=0;
			int bufferOverloaded=0;
			do{
                if(bufferOverloaded==0){
        				elemento[i]=caracter;
        				i++;
        				caracter=fgetc(archivo);      				
        				if (i>=TAMLEX){
        					msj_error("Longitud de Identificador excede tamaño de buffer",num_linea);
        					error=1;
        					bufferOverloaded=1;
                        }
                }
                else
                    caracter=fgetc(archivo);
			}while(isalpha(caracter) || isdigit(caracter));
			
			elemento[i]='\0';
			if (caracter!=EOF)
				ungetc(caracter,archivo);
		}
		else if (isdigit(caracter)){	
				i=0;
				estado=0;
				acepto=0;
				elemento[i]=caracter;
				
				while(!acepto){                
					switch(estado){
    					case 0: 
    						caracter=fgetc(archivo);
    						if (isdigit(caracter)){
    							elemento[++i]=caracter;
    							estado=0;
    						}
    						else if(caracter=='.'){
    							elemento[++i]=caracter;
    							estado=1;
    						}
    						else if(tolower(caracter)=='e'){
    							elemento[++i]='e';
    							estado=3;
    						}
    						else{
    							estado=6;
    						}
    						break;
    					
    					case 1:
    						caracter=fgetc(archivo);						
    						if (isdigit(caracter)){
    							elemento[++i]=caracter;
    							estado=2;
    						}
    						else{
    							estado=-1;
    							ungetc(caracter,archivo);
    						}
    						break;
    						
    					case 2:
    						caracter=fgetc(archivo);
    						if (isdigit(caracter))	{
    							elemento[++i]=caracter;
    							estado=2;
    						}
    						else if(tolower(caracter)=='e'){
                                 elemento[++i]='e';
    							estado=3;
    						}
    						else
    							estado=6;
    						break;
    						
    					case 3:
    						caracter=fgetc(archivo);
    						if (caracter=='+' || caracter=='-'){
    							elemento[++i]=caracter;
    							estado=4;
    						}
    						else if(isdigit(caracter)){
    							elemento[++i]=caracter;
    							estado=5;
    						}
    						else{
    							estado=-1;
    							ungetc(caracter,archivo);
    						}
    						break;
    						
    					case 4:
    						caracter=fgetc(archivo);
    						if (isdigit(caracter)){
    							elemento[++i]=caracter;
    							estado=5;
    						}
    						else{
    							estado=-1;
    							ungetc(caracter,archivo);
    						}
    						break;
    						
    					case 5:
    						caracter=fgetc(archivo);
    						if (isdigit(caracter)){
    							elemento[++i]=caracter;
    							estado=5;
    						}
    						else
    							estado=6;
    						break;
    					case 6:
    						if (caracter!=EOF)
    							ungetc(caracter,archivo);
    						i++;	
    						acepto=1;     
    						break;
    					case -1:
                            elemento[++i]='\0';
    						if (caracter==EOF)
    						    msj_error("No se esperaba fin de archivo!",num_linea);
                            else if(caracter=='\n')
                                msj_error("No se esperaba fin de linea!",num_linea);
                                else{
                                   msg[0]='\0';
    						       sprintf(msg,"No se esperaba '%c'",caracter);
    						       msj_error(msg,num_linea);
                                }
    						error=1;
    					    acepto=1;
				       }
 	            }
        }
        else if(caracter=='+'){
                elemento[i++]='+';
            }
        else if(caracter=='-'){
                elemento[i++]='-';
            }
        else if(caracter=='*'){
                elemento[i++]='*';
        }
        else if(caracter=='/'){
                elemento[i++]='/';
                caracter=fgetc(archivo);
                if(caracter=='/'){
                    num_linea++;
                    i=0;
                    caracter=fgetc(archivo);
                    while(!(caracter=='\n' || caracter==EOF))
                         caracter=fgetc(archivo);
                }
                else
                   ungetc(caracter,archivo);
        }
        else if(caracter=='('){
                elemento[i++]='(';
        }
        else if(caracter==')'){
                elemento[i++]=')';
        }
        else if(caracter==';'){
                elemento[i++]=';';
        }
        else if(caracter==','){
                elemento[i++]=',';
        }
        else if(caracter=='['){
                elemento[i++]='[';
        }
        else if(caracter==']'){
                elemento[i++]=']';
        }
		else if (caracter=='<') {
			
			elemento[i++]='<';
			caracter=fgetc(archivo);
			
			if (caracter=='>'){
                elemento[i++]='>';
			}
			else if (caracter=='='){
				elemento[i++]='=';
			}
			else
			    ungetc(caracter,archivo);
		}
		else if (caracter=='>'){
             elemento[i++]='>';
			
				caracter=fgetc(archivo);
			if (caracter=='=')
                  elemento[i++]='=';
			else
			    ungetc(caracter,archivo);
		}
		else if (caracter=='='){
		    elemento[i++]='=';
				caracter=fgetc(archivo);
			if (caracter=='=')
                  elemento[i++]='=';
            else
			    ungetc(caracter,archivo);
		}
		else if (caracter=='"'){
			i=0;
			elemento[i++]=caracter;
			do{
				caracter=fgetc(archivo);
				if (caracter=='"'){
				       elemento[i++]=caracter;
						break;
				}
				else if(caracter==EOF){
					msj_error("Se llego a fin de archivo sin finalizar un literal",num_linea);
					error=1;
					break;
				}
				else if(caracter=='\n'){
                    num_linea++;
					msj_error("Se llego a fin de linea sin finalizar un literal",num_linea);
					error=1;
					break;
                }
				else{
					elemento[i++]=caracter;
				}
			}while(isascii(caracter));
			
			elemento[i]='\0';
		}
		else if (caracter!=EOF){
            msg[0]='\0';
			sprintf(msg,"No se esperaba %c ",caracter);
			msj_error(msg,num_linea);
		}
		
	   if(i>0){
	        elemento[i]='\0';
	        convertir_a_minusculas(elemento);
            strcpy(pila_de_tokens[pos_pila].valor_token,elemento);
            pila_de_tokens[pos_pila++].num_linea=num_linea;
            }	
	
    }
    
}

int msj_error(char *msg,int num_linea){
    printf("Linea %d-->%s\n\n",num_linea,msg);
    printf("---------------------------------------------------------\n");
    }

int convertir_a_minusculas(char cad[]){
        int k=0;
        for(k=0;k<strlen(cad);k++){
            cad[k]=tolower(cad[k]);
        }
    }
    
//----- ANALIZADOR SINTACTICO -------------
int analizador_sintactico (token entrada[],int dim_pila){
    char pila[1000][30];
    int pos_pila=-1;
    int pos_entrada=0;
    int retorno=TRUE;
    int recuperado=FALSE;
    char msg[300];
    strcpy(pila[++pos_pila],"$");
    strcpy(pila[++pos_pila],"PROGRAMA");
    
    int analizar=TRUE;
    while(analizar==TRUE){
            char tope[30];
            char token_input[30];
            
            strcpy(tope,pila[pos_pila]);
            strcpy(token_input,entrada[pos_entrada].valor_token);
            
            if(strcmp(token_input,tope)==0){
                    if(strcmp(tope,"$")!=0){
                        match(token_input);
                        pos_pila--;
                        pos_entrada++;
                    }    
            }
            
            strcpy(tope,pila[pos_pila]);
            strcpy(token_input,entrada[pos_entrada].valor_token);
            
            int estado;
            estado=TOKENS_IGUALES;
            
            if(strcmp(tope,"PROGRAMA")==0) estado=PROGRAMA;
            if(strcmp(tope,"HEADER")==0) estado=HEADER;
            if(strcmp(tope,"HEADER2")==0) estado=HEADER2;
            if(strcmp(tope,"LISTA_SENT")==0) estado=LISTA_SENT;
            if(strcmp(tope,"DECLARACION")==0) estado=DECLARACION;
            if(strcmp(tope,"LISTAVAR")==0) estado=LISTAVAR;
            if(strcmp(tope,"LISTAVAR2")==0) estado=LISTAVAR2;
            if(strcmp(tope,"LISTA_SENT2")==0) estado=LISTA_SENT2;
            if(strcmp(tope,"SENTENCIA")==0) estado=SENTENCIA;
            if(strcmp(tope,"S_WRITE")==0) estado=S_WRITE;
            if(strcmp(tope,"S_WRITELN")==0) estado=S_WRITELN;
            if(strcmp(tope,"S_FOR")==0) estado=S_FOR;
            if(strcmp(tope,"S_IF")==0) estado=S_IF;
            if(strcmp(tope,"ELSE")==0) estado=ELSE;
            if(strcmp(tope,"BOOLEAN")==0) estado=BOOLEAN;
            if(strcmp(tope,"ASIGNACION")==0) estado=ASIGNACION;
            if(strcmp(tope,"IMPRIMIBLE")==0) estado=IMPRIMIBLE;
            if(strcmp(tope,"LITERAL")==0) estado=LITERAL;
            if(strcmp(tope,"EXP")==0) estado=EXP;
            if(strcmp(tope,"TERM")==0) estado=TERM;
            if(strcmp(tope,"FACTOR")==0) estado=FACTOR;
            if(strcmp(tope,"EXP2")==0) estado=EXP2;
            if(strcmp(tope,"TER2")==0) estado=TER2;
            if(strcmp(tope,"ADDOP")==0) estado=ADDOP;
            if(strcmp(tope,"MULOP")==0) estado=MULOP;
            if(strcmp(tope,"SIGNO")==0) estado=SIGNO;
            if(strcmp(tope,"ID")==0) estado=ID;
            if(strcmp(tope,"RECUPERACION")==0) estado=RECUPERACION;
            if(strcmp(tope,"ERROR")==0) estado=ERROR;
            if(strcmp(tope,"$")==0) estado=FIN;
            
            switch(estado){
                          
                case FIN: 
                          if(strcmp(token_input,"$")!=0)
                                strcpy(pila[++pos_pila],"ERROR");
                          else{
                                printf("Analisis completado!\n\n");
                                analizar=FALSE;
                          }
                          break;  
                          
                case PROGRAMA: 
                          if(strcmp(token_input,"var")==0){
                                strcpy(pila[pos_pila++],"LISTA_SENT");    
                                strcpy(pila[pos_pila],"HEADER");
                          }
                          else
                                strcpy(pila[pos_pila],"LISTA_SENT");    
                          break;
                
                case HEADER: 
                          strcpy(pila[pos_pila++],"HEADER2");    
                          strcpy(pila[pos_pila],"DECLARACION");            
                          break;
                          
                case HEADER2: 
                          if(strcmp(token_input,"var")==0)
                              strcpy(pila[++pos_pila],"DECLARACION");
                          else
                                pos_pila--;
                          break;

                case DECLARACION: 
                          strcpy(pila[pos_pila++],";");    
                          strcpy(pila[pos_pila++],"LISTAVAR");    
                          strcpy(pila[pos_pila],"var");
                          break;
                          
                case LISTAVAR: 
                          strcpy(pila[pos_pila++],"LISTAVAR2");    
                          strcpy(pila[pos_pila],"ID");
                          break;
                          
                case LISTAVAR2: 
                          if(strcmp(token_input,",")==0){ 
                              strcpy(pila[++pos_pila],"ID");
                              strcpy(pila[++pos_pila],",");
                          }
                          else
                              pos_pila--;
                          break;
                          
                case LISTA_SENT: 
                          strcpy(pila[pos_pila++],"LISTA_SENT2");
                          strcpy(pila[pos_pila++],";");
                          strcpy(pila[pos_pila],"SENTENCIA");
                          break;
                          
                case LISTA_SENT2: 
                          if(strcmp(token_input,"if")==0 ||strcmp(token_input,"for")==0||strcmp(token_input,"write")==0||strcmp(token_input,"writeln")==0||(es_identificador(token_input)&&es_pal_reservada(token_input)==0)||(token_input[0]<58&&token_input[0]>47)){
                               strcpy(pila[++pos_pila],";");
                               strcpy(pila[++pos_pila],"SENTENCIA");
                          }
                          else
                                if(recuperado==FALSE)
                                    pos_pila--;
                                else
                                    strcpy(pila[pos_pila],"RECUPERACION"); 
                          break;          
                          
                case SENTENCIA:
                          if(strcmp(token_input,"write")==0)
                               strcpy(pila[pos_pila],"S_WRITE");
                          else if(strcmp(token_input,"writeln")==0)
                                   strcpy(pila[pos_pila],"S_WRITELN");
                               else if(strcmp(token_input,"for")==0)
                                       strcpy(pila[pos_pila],"S_FOR");
                                    else if(strcmp(token_input,"if")==0)
                                            strcpy(pila[pos_pila],"S_IF");
                                         else if (es_identificador(token_input)&&es_pal_reservada(token_input)==0)
                                                  strcpy(pila[pos_pila],"ASIGNACION");
                                               else{
                                                   strcpy(pila[++pos_pila],"NOSENSE");             
                                                   strcpy(pila[++pos_pila],"ERROR");             
                                               }
                          break;
                          
                case S_WRITE:
                          strcpy(pila[pos_pila++],")");
                          strcpy(pila[pos_pila++],"IMPRIMIBLE");
                          strcpy(pila[pos_pila++],"(");
                          strcpy(pila[pos_pila],"write");
                          break;
                          
                case S_WRITELN:
                          strcpy(pila[pos_pila++],")");
                          strcpy(pila[pos_pila++],"IMPRIMIBLE");
                          strcpy(pila[pos_pila++],"(");
                          strcpy(pila[pos_pila],"writeln");
                          break;
                
                case IMPRIMIBLE:
                          if(token_input[0]=='"')
                              strcpy(pila[pos_pila],token_input);
                          else
                              strcpy(pila[pos_pila],"EXP");
                          break;
                          
                case S_IF:
                          strcpy(pila[pos_pila++],"if");
                          strcpy(pila[pos_pila++],"end");
                          strcpy(pila[pos_pila++],"LISTA_SENT");
                          strcpy(pila[pos_pila++],"ELSE");
                          strcpy(pila[pos_pila++],"LISTA_SENT");
                          strcpy(pila[pos_pila++],"then");
                          strcpy(pila[pos_pila++],"EXP");
                          strcpy(pila[pos_pila++],"BOOLEAN");
                          strcpy(pila[pos_pila++],"EXP");
                          strcpy(pila[pos_pila],"if");
                          break;
                          
                case ELSE:
                          if(strcmp(token_input,"else")==0)
                             pos_entrada++;
                          else
                               pos_pila--;
                               
                            pos_pila--;
                            break;
                             
                case BOOLEAN:
                          if(strcmp(token_input,"==")==0 ||strcmp(token_input,"<=")==0||strcmp(token_input,">=")==0||strcmp(token_input,">")==0||strcmp(token_input,"<")==0||strcmp(token_input,"<>")==0)
                              strcpy(pila[pos_pila],token_input);
                          else 
                              strcpy(pila[++pos_pila],"ERROR");
                          break;
                          
                case S_FOR:
                          strcpy(pila[pos_pila++],"for");
                          strcpy(pila[pos_pila++],"end");
                          strcpy(pila[pos_pila++],"LISTA_SENT");
                          strcpy(pila[pos_pila++],"do");
                          strcpy(pila[pos_pila++],"EXP");
                          strcpy(pila[pos_pila++],"step");
                          strcpy(pila[pos_pila++],"EXP");
                          strcpy(pila[pos_pila++],"to");
                          strcpy(pila[pos_pila++],"ASIGNACION");
                          strcpy(pila[pos_pila],"for");
                          break;
                     
                case ASIGNACION:
                          strcpy(pila[pos_pila++],"IMPRIMIBLE");
                          strcpy(pila[pos_pila++],"=");
                          strcpy(pila[pos_pila],"ID");
                          break;
                
                case ID: 
                          if(strcmp(entrada[pos_entrada+1].valor_token,"[")==0){  
                              strcpy(pila[pos_pila++],"]");             
                              strcpy(pila[pos_pila++],"EXP");            
                              strcpy(pila[pos_pila++],"[");            
                          }    
                          strcpy(pila[pos_pila],token_input);                  
                          break;
                          
                case EXP: 
                          strcpy(pila[pos_pila++],"EXP2");    
                          strcpy(pila[pos_pila],"TERM");
                          break;
                          
                case EXP2: 
                          if(strcmp(token_input,"+")==0 || strcmp(token_input,"-")==0){            
                              strcpy(pila[++pos_pila],"TERM");             
                              strcpy(pila[++pos_pila],"ADDOP");            
                          }
                          else
                              pos_pila--;
                          break;
                          
                case TERM:   
                          strcpy(pila[pos_pila++],"TER2");            
                          strcpy(pila[pos_pila],"FACTOR"); 
                          strcpy(pila[++pos_pila],"SIGNO");    
                          break;
                          
                case TER2:
                          if(strcmp(token_input,"*")==0 || strcmp(token_input,"/")==0){
                                strcpy(pila[++pos_pila],"FACTOR");     
                                strcpy(pila[++pos_pila],"SIGNO");        
                                strcpy(pila[++pos_pila],"MULOP");             
                           }
                           else
                                pos_pila--;
                           break;
                           
                case ADDOP:       
                           if(strcmp(token_input,"+")==0 || strcmp(token_input,"-")==0)
                                strcpy(pila[pos_pila],token_input);
                           else
                                strcpy(pila[++pos_pila],"ERROR");
                           break;
                           
                case MULOP:
                           if(strcmp(token_input,"*")==0 || strcmp(token_input,"/")==0)
                                strcpy(pila[pos_pila],token_input);
                           else
                                strcpy(pila[++pos_pila],"ERROR");
        
                          break;
                          
                case FACTOR: 
                          if(strcmp(token_input,"(")==0) {
                               strcpy(pila[pos_pila++],")"); 
                               strcpy(pila[pos_pila++],"EXP");
                               strcpy(pila[pos_pila],"(");
                          } 
                          else if(es_identificador(token_input)&&es_pal_reservada(token_input)==0)
                                           strcpy(pila[pos_pila],"ID");  
                                else if(es_numero(token_input))
                                         strcpy(pila[pos_pila],token_input);
                                     else 
                                         strcpy(pila[++pos_pila],"ERROR");
                                     
                         break;
                         
                case RECUPERACION:   
                        retorno=FALSE;   
                        recuperado=TRUE;
                        if(strcmp(token_input,"$")!=0){
                                int k;
                                int seguir_analizando=0;
                                for(k=pos_entrada;k<dim_pila-1;k++){
                                    if(conj_pro_sentencia(entrada[k].valor_token)==1||(es_identificador(entrada[k].valor_token)&&es_pal_reservada(entrada[k].valor_token)==0) ){
                                        if(strcmp(entrada[k].valor_token,"var")==0)
                                            msj_error("Las variables solo se pueden declarar al principio del programa!",entrada[k].num_linea);
                                        else{
                                                if(!((strcmp(entrada[k].valor_token,"if")==0||strcmp(entrada[k].valor_token,"for")==0)&&strcmp(entrada[k-1].valor_token,"end")==0)){
                                                    pos_entrada=k;
                                                    seguir_analizando=1;
                                                    break;
                                                }
                                            }
                                     }
                                }
                                if(seguir_analizando==1){
                                    pos_pila=3;          
                                    strcpy(pila[0],"$");
                                    strcpy(pila[1],"LISTA_SENT2");
                                    strcpy(pila[2],";");
                                    strcpy(pila[3],"SENTENCIA");
                                }
                                else 
                                    analizar=FALSE;
                        } 
                        else
                            pos_pila=0;
                                                 
                        break;
                case SIGNO: 
                            if(entrada[pos_entrada].valor_token[0]=='-' ||entrada[pos_entrada].valor_token[0]=='+')
                                pos_entrada++;
                            pos_pila--;
                     break;
                
                case TOKENS_IGUALES:
                             if(strcmp(tope,token_input)==0){
                                match(token_input);
                                pos_pila--;
                                pos_entrada++;
                             }
                             else 
                                 strcpy(pila[++pos_pila],"ERROR");
                     break;
                    
                case ERROR:
                          if(strcmp(token_input,"$")==0)
                              msj_error("No se esperaba fin de archivo!",entrada[pos_entrada-1].num_linea);
                          else{
                               msg[0]='\0';
                               if(strcmp(pila[pos_pila-1],"FACTOR")==0){
                                    sprintf(msg,"Se esperaba EXPRESION despues de token '%s'",entrada[pos_entrada-1].valor_token);
                                     msj_error(msg,entrada[pos_entrada-1].num_linea);
                               }
                               else if(strcmp(pila[pos_pila-1],"NOSENSE")==0){
                                        sprintf(msg,"No se esperaba '%s'",entrada[pos_entrada].valor_token);
                                        msj_error(msg,entrada[pos_entrada].num_linea);           
                                    }
                                     else if(strcmp(pila[pos_pila-1],"BOOLEAN")==0){
                                              sprintf(msg,"Se esperaba Operador Relacional despues de token '%s'",entrada[pos_entrada-1].valor_token);
                                              msj_error(msg,entrada[pos_entrada-1].num_linea);           
                                          }
                                          else{
                                              sprintf(msg,"Se esperaba '%s' despues de token '%s'",pila[pos_pila-1],entrada[pos_entrada-1].valor_token);
                                              msj_error(msg,entrada[pos_entrada-1].num_linea);
                                          }
                          }
                          strcpy(pila[pos_pila],"RECUPERACION");
                break;
                            
            }      
    }
    return retorno;
}

int match(char *elemento){
    
    return 0;    
}

int es_identificador(char *cad){
        int es_id=0;
        int pos=0;
       
        if(isalpha(cad[0])){
            pos++;
            while(isalpha(cad[pos])||isdigit(cad[pos])|| cad[pos]=='_') 
                  pos++;
            
            if(pos==strlen(cad))
                es_id=1;
        }   
return es_id;
}

int es_pal_reservada(char *cad){
        char *pal_reservada[]={"for","if","end","step","to","var","else","do","then"};
        int es_reservada=0;
                int k=0;
                for(k=0;k<9;k++){
                    if(strcmp(cad,pal_reservada[k])==0){
                        es_reservada=1;
                        break;
                    }    
                }
return es_reservada;
}

int conj_pro_sentencia(char *cad){
        char *pal_reservada[]={"for","if","writeln","write","var"};
        int es_reservada=0;
                int k=0;
                for(k=0;k<5;k++){
                    if(strcmp(cad,pal_reservada[k])==0){
                        es_reservada=1;
                        break;
                    }    
                }
return es_reservada;
}

int es_numero(char *cad){
        int es_num=1;
        int pos=0;
        while(pos<strlen(cad)){
                if(!(isdigit(cad[pos])||cad[pos] =='e' || cad[pos]=='.')){
                    es_num=0;
                    break;
                }
                pos++;
        }
return es_num;
}

