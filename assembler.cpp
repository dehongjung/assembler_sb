/*
  Universidade de Brasilia
  Departamento de Ciencia da Computacao
  Software Basico
  Trabalho 1: Montador
  Integrantes: De Hong Jung 10/0098207
               Camila Brito 12/0008882
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstddef> 
#include <vector>
#include <sstream>
#include <stdlib.h> 
#include <iomanip>


using namespace std;


//Funcao que transforma uma string de operacoes em valores inteiros.
int str2int(std::string token){
  if (token == "add")
    return 1;
  else if (token == "sub")
    return 2;
  else if (token == "mult")
    return 3;
  else if (token == "div")
    return 4;
  else if (token == "jmp")
    return 5;
  else if (token == "jmpn")
    return 6;
  else if (token == "jmpp")
    return 7;
  else if (token == "jmpz")
    return 8;
  else if (token == "copy")
    return 9;
  else if (token == "load")
    return 10;
  else if (token == "store")
    return 11;
  else if (token == "input")
    return 12;
  else if (token == "output")
    return 13;
  else if (token == "stop")
    return 14;
  else if (token == "begin")
    return 15;
  else if (token == "end")
    return 16;
  else if (token == "space")
    return 17;
  else if (token == "const")
    return 18;
  else if (token == "public")
    return 19;
  else if(token == "extern")
    return 20;
  else if (token == "section")
    return 21;
  else if (token == "text")
    return 22;
  else if (token == "data")
    return 23;
  else if (token == "0")
    return 0;
  else if (token == "15")
    return 15;
  else
    return -1;
} 

//Funcao que transforma uma string em seu respectivo valor inteiro (tanto hexadecimal quanto decimal).
int String_To_Int(std::string token){
  int x;
  std::stringstream ss;

  if((token[0] == '0' && token[1] == 'x') || (token[0] == '-' && token[1] == '0' && token[2] == 'x')){
    ss << std::hex << token;
    ss >> x;
    return x;
  }
  else
    return(atoi(token.c_str()));
}

//Funcao que transforma todos os caracteres da string em letra minuscula
std::string String_To_Lower(std::string line)
{
    for (unsigned int i = 0; i < line.size(); ++i){
      line[i] = tolower(line[i]);
    }

    return(line);
}

//Funcao que elimina os comentarios da linha. In: string/ Out: string sem comentarios.
std::string Elimina_Comentario(std::string line){

  std::size_t found = line.find_first_of(";");

  if (found!=std::string::npos){
    line = line.substr(0,found);
    return(line);
  }
  else
    return(line);
  
}

//Funcao que elimina as virgulas de um token. In: string/ Out: string sem virgulas.
std::string Elimina_Virgula(std::string line){

  std::size_t found = line.find_first_of(",");
  if (found!=std::string::npos){
    line = line.substr(0, found);
    return(line);
  }
  else
    return(line);
}

//Funcao que elimina os dois pontos do token. In: string/ Out: string sem dois pontos.
std::string Elimina_Dois_Pontos(std::string line){

  std::size_t found = line.find_first_of(":");

  if (found!=std::string::npos){
    line = line.substr(0,found);
    return(line);
  }
  else
    return(line);
  
}

//Funcao que separa os tokens de cada linha. In: string/ Out: vetor de strings(tokens)
vector<string> Separa_Tokens(std::string line){
  string buf;
  stringstream ss(line);
  vector<string> tokens;

  while (ss >> buf)
    tokens.push_back(buf);

  return(tokens);
}

//Funcao que separa os tokens de um token delimitado por "+"
vector<string> Separa_Tokens_Plus(std::string line){
  vector<string> tokens;
  std::size_t found = line.find_first_of("+");
  std::size_t found2 = line.find_first_of("[");
  std::size_t found3 = line.find_first_of("]");
  if (found!=std::string::npos){
    tokens.push_back(line.substr(0,found));
    tokens.push_back(line.substr(found+1, line.size()-found));
  }
  else if (found2!=std::string::npos){
    tokens.push_back(line.substr(0,found2));
    tokens.push_back(line.substr(found2+1, line.size()-found3));
  }
  else
    tokens.push_back(line);  

  return(tokens);
}

//Funcao que verifica se o token é invalido
bool Token_Invalido(std::string token){
  std::size_t found = token.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_[]");
  std::size_t found2;
  string new_token;

  if (token.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_[]") != std::string::npos)
    return true;
  else if (found != 0)
    return true;
  else
    return false;
}

//Funcao que verifica se o token é invalido (numeros)
bool Token_Invalido_Num(std::string token){
  std::size_t found2;
  string new_token;

  if (token[0] == '0'&& token[1] == 'x'){
    new_token = token.substr(2, token.size()-2);
    found2 = new_token.find_first_not_of("abcdef1234567890");
    if (found2 != std::string::npos){
      return true;
    }
    else
      return false;
  }

  else if (token[0] == '-' && token[1] == '0' && token[2] == 'x'){
    new_token = token.substr(3, token.size()-3);
    found2 = new_token.find_first_not_of("abcdef1234567890");
    if (found2 != std::string::npos){
      cout << found2 << endl;
      return true;
    }
    else
      return false;
  }

  else if (token.find_first_not_of("abcdefghijklmnopqrstuvwxyz01234567890") != std::string::npos)
    return true;
  else
    return false;
}


//Funcao que verifica se o token é invalido (delimitado por "+")
bool Token_Invalido_Plus(std::string token){
  std::size_t found = token.find_first_of("+");
  vector<string> tokens;

  if (token[0] == '+' || token[token.size()-1] == '+'){
    return true;
  }
  else if (found == std::string::npos){
    return Token_Invalido(token);
  }
  else{
    tokens = Separa_Tokens_Plus(token);
    if(Token_Invalido(tokens[0]) == true || Token_Invalido_Num(tokens[1]) == true){
      return true;
    }
    else
      return false;
  }
  
}


//Funcao que verifica se ha um rotulo na linha
bool Verifica_Rotulo(std::string token, int line_counter){
  std::size_t found = token.find_first_of(":");
  if (found!=std::string::npos){
    if (str2int(Elimina_Dois_Pontos(token)) != -1)
      cout << "[Erro Sintatico] Linha: " << line_counter << endl;
    if ((token.size()-1) == found)
      return true;
    else{
      cout << "[Erro Lexico] Linha " << line_counter << endl;
      return false;
    }
  }
  else
    return false;
}

//Funcao Segunda Passagem
void Segunda_Passagem(vector<string> TS_rotulos, vector<int> TS_end, vector<string> vetor_auxiliar, vector<int> TS_const, std::string nome_objeto, vector<string> TD_rotulos, vector<int> TD_end, vector<string> TU_ocorrencias, vector<int> TU_end, int flag_TEXT_end, vector<int> TS_space, vector<int> TS_extern, int flag_ERRO){
  vector<int> codigo_objeto; 
  int operacao, j, flag_TS = 0, k = 0;
  vector<string> vetor_plus;  //Vetor para separar o operando <rot+numero> em <rot> e <numero> 
  string linex;
  std::size_t found;

  ofstream arquivo_objeto (nome_objeto.c_str());

  for (int i = 0; i < vetor_auxiliar.size() ; i++){
    operacao = str2int(vetor_auxiliar[i]);

    switch(operacao){
      case 1:case 2:case 3:case 10:case 12:case 13:
        codigo_objeto.push_back(operacao);
        i++;
        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);
        if (vetor_plus.size() == 1){
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_auxiliar[i] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              codigo_objeto.push_back(TS_end[j]);
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;

        }else{
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_plus[0] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              if (vetor_auxiliar[i].find_first_of("+") != std::string::npos){//-----------------------
                if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                  cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                  flag_ERRO = 1;
                }
              }
              else{
                if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                  cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                  flag_ERRO = 1;
                }
              }
              codigo_objeto.push_back(TS_end[j]+String_To_Int(vetor_plus[1]));
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        //i++;
        break;

      case 5:case 6:case 7:case 8: //JMP
        codigo_objeto.push_back(operacao);
        i++;
        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);
        if (vetor_plus.size() == 1){
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_auxiliar[i] == TS_rotulos[j]){
              if (TS_space[j] >= 1 || TS_const[j] == 1){
                cout << "[Erro Semantico] Pulo para rotulo invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              codigo_objeto.push_back(TS_end[j]);
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;

        }else{
          for(j = 0; j < TS_rotulos.size(); j++){

            if(vetor_plus[0] == TS_rotulos[j]){
              if (TS_space[j] >= 1 || TS_const[j] == 1){
                cout << "[Erro Semantico] Pulo para rotulo invalido: "<< TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }

              if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                flag_ERRO = 1;
              }

              codigo_objeto.push_back(TS_end[j]+String_To_Int(vetor_plus[1]));
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        //i++;
        break;


      case 4: //DIV
        codigo_objeto.push_back(operacao);
        i++;
        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);

        if (vetor_plus.size() == 1){
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_plus[0] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              if ((flag_TEXT_end == 0 && vetor_auxiliar[TS_end[j]] == "0") || (flag_TEXT_end == 1 && vetor_auxiliar[TS_end[j]+1] == "0") ){
                cout << "[Erro Semantico] Divisao por Zero" << endl;
                flag_ERRO = 1;
              }else
                codigo_objeto.push_back(TS_end[j]);
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        else{
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_plus[0] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                flag_ERRO = 1;
              }

              if (vetor_auxiliar[TS_end[j]] == "0"){
                cout << "[Erro Semantico] Divisao por Zero" << endl;
                flag_ERRO = 1;
              }else
                codigo_objeto.push_back(TS_end[j] + String_To_Int(vetor_plus[1]));
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        
        
        //i++;
        break;

      case 9:  //COPY
        codigo_objeto.push_back(operacao);
        i++;
        
        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);

        for(j = 0; j < TS_rotulos.size(); j++){
          if(vetor_plus[0] == TS_rotulos[j]){
            if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
              cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
              flag_ERRO = 1;
            }

            if (vetor_plus.size() == 1)
              codigo_objeto.push_back(TS_end[j]);
            else{
              if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                flag_ERRO = 1;
              }

              codigo_objeto.push_back(TS_end[j] + String_To_Int(vetor_plus[1]));
            }
            flag_TS = 1;
          }
        }
        if(flag_TS == 0){
          cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
          flag_ERRO = 1;
        }
        flag_TS = 0;
        i++;

        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);


        for(j = 0; j < TS_rotulos.size(); j++){

          if(vetor_plus[0] == TS_rotulos[j]){
            if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
              cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
              flag_ERRO = 1;
            }
            //Verifica se ha modificacao de valor constante
            if (TS_const[j] == 1){
              cout << "[Erro Semantico] Modificacao de valor constante: " << vetor_plus[0] << endl;
              flag_ERRO = 1;
            }

            if (vetor_plus.size() == 1)
              codigo_objeto.push_back(TS_end[j]);
            else{
              if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                flag_ERRO = 1;
              }

              codigo_objeto.push_back(TS_end[j] + String_To_Int(vetor_plus[1]));
            }
            flag_TS = 1;
          }
        }
        if(flag_TS == 0){
          cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
          flag_ERRO = 1;
        }
        flag_TS = 0;
        //i++;
        break;

      case 11: //STORE
        codigo_objeto.push_back(operacao);
        i++;

        vetor_plus = Separa_Tokens_Plus(vetor_auxiliar[i]);
        if (vetor_plus.size() == 1){
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_auxiliar[i] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              //Verifica se ha modificacao de valor constante
              if (TS_const[j] == 1){
                cout << "[Erro Semantico] Modificacao de valor constante: " << vetor_plus[0] << endl;
                flag_ERRO = 1;
              }
              codigo_objeto.push_back(TS_end[j]);
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        else{
          for(j = 0; j < TS_rotulos.size(); j++){
            if(vetor_plus[0] == TS_rotulos[j]){
              if (TS_space[j] == 0 && TS_const[j] == 0 && TS_extern[j] == 0){
                cout << "[Erro Semantico] Operando Invalido: " << TS_rotulos[j] << endl;
                flag_ERRO = 1;
              }
              if ((String_To_Int(vetor_plus[1]) + 1 > TS_space[j]) && (TS_extern[j] != 1)){
                cout << "[Erro Semantico] Espaco de memoria nao reservado" << endl;
                flag_ERRO = 1;
              }

              //Verifica se ha modificacao de valor constante
              if (TS_const[j] == 1){
                cout << "[Erro Semantico] Modificacao de valor constante: " << vetor_plus[0] << endl;
                flag_ERRO = 1;
              }
              codigo_objeto.push_back(TS_end[j]+String_To_Int(vetor_plus[1]));
              flag_TS = 1;
            }
          }
          if(flag_TS == 0){
            cout << "[Erro Semantico] Nao declarou a variavel: " << vetor_auxiliar[i] << endl;
            flag_ERRO = 1;
          }
          flag_TS = 0;
        }
        //i++;
        break;

      case 14: //STOP
        codigo_objeto.push_back(operacao);
        break;

      case 15: //FIM DE TEXT
        codigo_objeto.push_back(operacao);
        break;

      case 0: //SPACE
        codigo_objeto.push_back(operacao);
        break;

      case -1: //CONST
        codigo_objeto.push_back(String_To_Int(vetor_auxiliar[i]));
        break;

    }
  }
  cout << endl;
  
  //ESCRITA NO ARQUIVO OBJETO
  if (arquivo_objeto.is_open() && flag_ERRO == 0){
    arquivo_objeto << "TABLE USE\n";
    for (k = 0; k < TU_ocorrencias.size(); k++){
      arquivo_objeto << TU_ocorrencias[k] << " " << TU_end[k] << endl;
    }
    arquivo_objeto << "\n";

    arquivo_objeto << "TABLE DEFINITION\n";
    for (k = 0; k < TD_rotulos.size(); k++){
      arquivo_objeto << TD_rotulos[k] << " " << TD_end[k] << endl;
    }
    arquivo_objeto << "\n";

    arquivo_objeto << "CODE\n";
    for (k = 0; k < codigo_objeto.size(); k++){
      arquivo_objeto << codigo_objeto[k] << " ";
    }
    arquivo_objeto << "\n";

    arquivo_objeto.close();

    //PRINT CODE
    cout << "CODE" << endl;
    for(j = 0; j < codigo_objeto.size(); j++)
        cout << codigo_objeto[j] << " ";
    cout << endl;
    cout << endl;
  }
  else 
    cout << "Arquivo Objeto nao foi gerado." << endl;

//TESTE DO ARQUIVO OBJETO

 /* if (arquivo_objeto.is_open())
  {
    while ( getline (arquivo_objeto,linex) )
    {
      cout << linex << '\n';
    }
    arquivo_objeto.close();
  }
  else cout << "Unable to open file";*/


}

//Funcao Primeira Passagem
void Primeira_Passagem(std::string nome_asm, std::string nome_objeto){

  string line;
  int PC = 0, line_counter = 0, line_mvp = 0, j =0, index, operacao, flag_TEXT = 0, flag_DATA = 0, i = 0, flag_TS = 0, flag_STOP = 0, flag_TEXT_end = 0, flag_ERRO = 0;
  vector<string> tokens, aux, vetor_auxiliar, TS_rotulos, TD_rotulos, TU_rotulos, TU_ocorrencias;
  vector<int> TS_end, TS_const, TD_end, TU_end, TS_space, TS_extern;

  ifstream codigo_fonte (nome_asm.c_str());
  if (codigo_fonte.is_open())
  {
    while ( getline (codigo_fonte,line) )
    {

      line_counter++;
      line = Elimina_Comentario(line);
      line = String_To_Lower(line);
      tokens = Separa_Tokens(line);

      
      if (!tokens.empty()){
        line_mvp++;

        //Verifica se tem token invalido na linha
        /*for (i = 0; i < tokens.size(); i++){
          if(Token_Invalido(tokens[i]))
            cout << "[Erro Lexico] Linha: " << line_counter << endl;
        }*/



        //Verifica se o codigo comeca com SECTION TEXT
        if((tokens[0].compare("section") || tokens[1].compare("text")) && line_mvp
         == 1){
          cout << "[Erro Sintatico] Linha " << line_counter << endl;
          flag_TEXT = 0;
          flag_ERRO = 1;
        }else
          flag_TEXT = 1;

        //Verifica se aparece o SECTION DATA  
        if(tokens[0].compare("section") == 0 && tokens[1].compare("data") == 0){
          flag_DATA = 1;
        }

        //Verifica se tem rotulo e insere na Tabela de Simbolos
        if(Verifica_Rotulo(tokens[0], line_counter)){
          tokens[0] = Elimina_Dois_Pontos(tokens[0]);

          if(Token_Invalido(tokens[0])){
            cout << "[Erro Lexico] Linha: " << line_counter << endl;
            flag_ERRO = 1;
          }

          //Verifica se o rotulo ja existe na TS
          for(j = 0; j < TS_rotulos.size(); j++){
            if(tokens[0] == TS_rotulos[j]){
              flag_TS = 1;
              cout << "[Erro Semantico] Linha: " << line_counter << endl;
              flag_ERRO = 1;
            }
          }
          if (flag_TS ==0){
            
            TS_rotulos.push_back (tokens[0]);
            TS_end.push_back (PC);
            TS_const.push_back (0);
            TS_space.push_back (0);
            TS_extern.push_back (0);
            index = 1;
            operacao = str2int(tokens[1]);
            
          }
          flag_TS = 0;
        }else{
          index = 0;
          operacao = str2int(tokens[0]);
        }
        //Verifica se as operacoes e o numero de operandos estao corretos
        switch(operacao){
          case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 10:case 11:case 12:case 13:
            PC++;
            if(flag_TEXT == 1 && flag_DATA == 0){
              if (tokens.size() == 2 + index) {
                PC++;
                vetor_auxiliar.push_back (tokens[index]);
                vetor_auxiliar.push_back (tokens[index+1]);
              }

              else{
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }

            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl; 
              flag_ERRO = 1;    
            }

            //Verifica se tem token invalido na linha
            for (i = index+1; i < tokens.size(); i++){
              if(Token_Invalido_Plus(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }

            for (int h = 0; h < TU_rotulos.size(); h++)
            {
              aux = Separa_Tokens_Plus(tokens[index+1]);
              tokens[index+1] = aux[0];
              if(tokens[index+1] == TU_rotulos[h]) {
                TU_ocorrencias.push_back(tokens[index+1]);
                TU_end.push_back(PC-1);
              }
            }
            break;

          case 9:  //COPY
            PC++;
            if(flag_TEXT == 1 && flag_DATA == 0){
              if (tokens.size() == 3 + index) {
                PC = PC + 2;

                tokens[index+1] = Elimina_Virgula(tokens[index+1]);

                vetor_auxiliar.push_back (tokens[index]);
                vetor_auxiliar.push_back (tokens[index+1]);
                vetor_auxiliar.push_back (tokens[index+2]);

                for (int g = 0; g < TU_rotulos.size(); g++)
                {
                  aux = Separa_Tokens_Plus(tokens[index+1]);
                  tokens[index+1] = aux[0];
                  if(tokens[index+1] == TU_rotulos[g]) {
                    TU_ocorrencias.push_back(tokens[index+1]);
                    TU_end.push_back(PC-2);
                  }
                  aux = Separa_Tokens_Plus(tokens[index+2]);
                  tokens[index+2] = aux[0];
                  if(tokens[index+2] == TU_rotulos[g]) {
                    TU_ocorrencias.push_back(tokens[index+2]);
                    TU_end.push_back(PC-1);
                }
            }
              }

              else{
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }

            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              //cout << tokens[index+1] << " " << tokens[index + 2] << endl;
              if(Token_Invalido_Plus(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }

            
            break;

          case 14:  //STOP
            PC++;
            if(flag_TEXT == 1 && flag_DATA == 0){
              vetor_auxiliar.push_back (tokens[index]);
              if (tokens.size() != 1 + index) {
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            flag_STOP = 1;
            break;

          case 15:  //BEGIN
             if(flag_TEXT == 1 && flag_DATA == 0){
              if (tokens.size() != 1 + index) {
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            break;

          case 20: // EXTERN
            if(flag_TEXT == 1 && flag_DATA == 0){
              if (tokens.size() != 1 + index) {
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            TS_extern[TS_extern.size()-1] = 1;
            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }

            TU_rotulos.push_back(tokens[0]);
            break;

          case 16:  //END
            if(flag_DATA == 1){
              if (tokens.size() != 1 + index) {
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            break;

          case 17: //SPACE
            if (flag_STOP == 0 && flag_TEXT_end == 0){
              vetor_auxiliar.push_back("15");
              flag_TEXT_end = 1;
            }


            if(flag_DATA == 1){
              if (tokens.size() == 3){
                //Verifica argumentos invalidos
                if (String_To_Int(tokens[2]) <= 0){
                  //if (tokens[2] != "0")
                  cout << "[Erro Sintatico] Linha: " << line_counter << endl;
                  flag_ERRO = 1;
                }

                PC = PC + String_To_Int(tokens[2]);
                TS_space[TS_space.size()-1] = String_To_Int(tokens[2]);
                for (i = 0; i < String_To_Int(tokens[2]); i++){
                  vetor_auxiliar.push_back ("0");
                }
                //TS_const.push_back (0);
              }
              else if (tokens.size() == 2) {
                PC++;
                vetor_auxiliar.push_back ("0");

                TS_space[TS_space.size()-1] = 1;
                //TS_const.push_back (0);
              }
              else{
                cout << "[Erro Sintatico] Linha " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            else{
              cout << "[Erro Semantico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index+1; i < tokens.size(); i++){
              if(Token_Invalido_Num(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            break;

          case 18: // CONST
            if (flag_STOP == 0 && flag_TEXT_end == 0){
              vetor_auxiliar.push_back("15");
              flag_TEXT_end = 1;
            }


            PC++;
            if (tokens.size() != 2 + index) {
              cout << "[Erro Sintatico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }
            else
              //Verifica argumentos invalidos
              if (String_To_Int(tokens[2]) == 0){
                if (tokens[2] != "0"){
                  cout << "[Erro Sintatico] Linha: " << line_counter << endl;
                  flag_ERRO = 1;
                }
              }
              vetor_auxiliar.push_back (tokens[index+1]);
              TS_const[TS_const.size()-1] = 1;

            //Verifica se tem token invalido na linha
            for (i = index+1; i < tokens.size(); i++){
              if(Token_Invalido_Num(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            break;

          case 19: //PUBLIC     TABELA DE DEFINICAO
            if (tokens.size() != 2 + index) {
              cout << "[Erro Sintatico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }
            TD_rotulos.push_back(tokens[1]);

            //Verifica se tem token invalido na linha
            for (i = index=1; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }
            break;

          case 21: //SECTION
            if (flag_DATA && tokens.size() != 2 && line_mvp != 1){
              cout << "[Erro Sintatico] Linha " << line_counter << endl; 
              flag_ERRO = 1;
            }

            if (flag_TEXT && tokens.size() != 2 && line_mvp == 1){
              cout << "[Erro Sintatico] Linha " << line_counter << endl;
              flag_ERRO = 1;
            }

            if (flag_TEXT && tokens[1] != "data" && line_mvp != 1){
              cout << "[Erro Sintatico] Linha " << line_counter << endl; 
              flag_ERRO = 1;
            }

            //Verifica se tem token invalido na linha
            for (i = index+1; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i])){
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
                flag_ERRO = 1;
              }
            }

            break;

          default:
            cout << "[Erro Sintatico] Linha " << line_counter << endl;
            flag_ERRO = 1;
            //Verifica se tem token invalido na linha
            for (i = index; i < tokens.size(); i++){
              if(Token_Invalido(tokens[i]))
                cout << "[Erro Lexico] Linha: " << line_counter << endl;
            }
            break;

        }
      }
    }
    if(flag_DATA == 0 || flag_TEXT == 0) {
      cout << "[Erro Semantico] Nao tem Section Text ou Data" << endl;
      flag_ERRO = 1;
    }

    //TABELA DE DEFINICAO
    for (int k = 0; k < TD_rotulos.size(); k++){
      for (int l = 0; l < TS_rotulos.size(); l++)
      {
        if(TD_rotulos[k] == TS_rotulos[l]) {
          TD_end.push_back(TS_end[l]);
        }
      }
    }

    Segunda_Passagem(TS_rotulos, TS_end, vetor_auxiliar, TS_const, nome_objeto, TD_rotulos, TD_end, TU_ocorrencias, TU_end, flag_TEXT_end, TS_space, TS_extern, flag_ERRO);
    codigo_fonte.close();
  }

  else 
    cout << "Unable to open file"; 

}

//MAIN
int main (int argc, char **argv) {
  string nome_asm, nome_objeto;
  std::string arg1(argv[1]);
  std::string arg2(argv[2]);

  //Checa o numero de argumentos
  if(argc > 3)
    cout << "Erro! Numero de parametros maior do que dois!" << endl;
  
  //Define o nome dos arquivos
  nome_asm = arg1 + ".asm";
  nome_objeto = arg2 + ".o";

  Primeira_Passagem(nome_asm.c_str(), nome_objeto.c_str());
  //cout << endl;

  return 0;
}