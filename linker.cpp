/*
  Universidade de Brasilia
  Departamento de Ciencia da Computacao
  Software Basico
  Trabalho 1: Ligador
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

//Funcao que separa os tokens de cada linha. In: string/ Out: vetor de strings(tokens)
vector<string> Separa_Tokens(std::string line){
  string buf;
  stringstream ss(line);
  vector<string> tokens;

  while (ss >> buf)
    tokens.push_back(buf);

  return(tokens);
}


//MAIN
int main (int argc, char **argv) {
  string nome_objeto1, nome_objeto2, nome_executavel;
  string line1, line2;
  vector<string> tokens, TU1_rotulos, TU2_rotulos, TD1_rotulos, TD2_rotulos;
  vector<int> TU1_end, TU2_end, TD1_end, TD2_end, codigo1, codigo2, codigo_executavel; 
  int i = 0, j = 0, fator_correcao2, flag_check = 0, found, flag_ERRO = 1;
  std::string arg1(argv[1]);
  std::string arg2(argv[2]);
  std::string arg3(argv[3]);

  //Checa o numero de argumentos
  if(argc > 4)
    cout << "Erro! Numero de parametros maior do que tres!" << endl;
  
  //Define o nome dos arquivos
  nome_objeto1 = arg1 + ".o";
  nome_objeto2 = arg2 + ".o";
  nome_executavel = arg3 + ".e";

  //CODIGO 1
  ifstream codigo_objeto1 (nome_objeto1.c_str());
  if (codigo_objeto1.is_open())
  {
    getline (codigo_objeto1,line1);  //Descarta a primeira linha

    tokens = Separa_Tokens(line1);
    //Tabela de Uso 1
    while (!tokens.empty()){
      getline (codigo_objeto1,line1);
      tokens = Separa_Tokens(line1);
      if (!tokens.empty()){
        TU1_rotulos.push_back(tokens[0]);
        TU1_end.push_back(String_To_Int(tokens[1]));
      }
    }

    getline (codigo_objeto1,line1);
    tokens = Separa_Tokens(line1);

    //Tabela de Definicao 1
    while (!tokens.empty()){
      getline (codigo_objeto1,line1);
      tokens = Separa_Tokens(line1);
      if (!tokens.empty()){
        TD1_rotulos.push_back(tokens[0]);
        TD1_end.push_back(String_To_Int(tokens[1]));
      }
    }

    getline (codigo_objeto1,line1);
    getline (codigo_objeto1,line1);
    tokens = Separa_Tokens(line1);

    //Codigo Objeto 1
    for (i = 0; i < tokens.size(); i++){
      codigo1.push_back(String_To_Int(tokens[i]));
    }
    fator_correcao2 = codigo1.size();

  }
  else 
    cout << "Unable to open file"; 

  //-----------------------------------------------------------------------
  //CODIGO 2
  ifstream codigo_objeto2 (nome_objeto2.c_str());
  if (codigo_objeto2.is_open())
  {
    getline (codigo_objeto2,line2);  //Descarta a primeira linha

    tokens = Separa_Tokens(line2);
    //Tabela de Uso 2
    while (!tokens.empty()){
      getline (codigo_objeto2,line2);
      tokens = Separa_Tokens(line2);
      if (!tokens.empty()){
        TU2_rotulos.push_back(tokens[0]);
        TU2_end.push_back(String_To_Int(tokens[1]));
      }
    }

    getline (codigo_objeto2,line2);
    tokens = Separa_Tokens(line2);

    //Tabela de Definicao 2
    while (!tokens.empty()){
      getline (codigo_objeto2,line2);
      tokens = Separa_Tokens(line2);
      if (!tokens.empty()){
        TD2_rotulos.push_back(tokens[0]);
        TD2_end.push_back(String_To_Int(tokens[1]));
      }
    }

    getline (codigo_objeto2,line2);
    getline (codigo_objeto2,line2);
    tokens = Separa_Tokens(line2);

    //Codigo Objeto 2
    for (i = 0; i < tokens.size(); i++){
      codigo2.push_back(String_To_Int(tokens[i]));
    }
  
  }
  else 
    cout << "Unable to open file" << endl; 
  //-----------------------------------------------------------------------
  //Verificacao
  for (i = 0; i < TU1_rotulos.size(); i++){
    for (j = 0; j < TD2_rotulos.size(); j++){
      if (TU1_rotulos[i] == TD2_rotulos[j]){
        flag_ERRO = 0;
        break;
      }else
        flag_ERRO = 1;
    }
    if (flag_ERRO == 1)
      break;
  }
  if (flag_ERRO == 0){
    for (i = 0; i < TU2_rotulos.size(); i++){
      for (j = 0; j < TD1_rotulos.size(); j++){
        if (TU2_rotulos[i] == TD1_rotulos[j]){
          flag_ERRO = 0;
          break;
        }else
          flag_ERRO = 1;
      }
      if (flag_ERRO == 1)
        break;
    }
  }

  if (flag_ERRO == 0){
    //-----------------------------------------------------------------------
    //Ligar o Codigo 1

    for (i = 0; i < TU1_rotulos.size(); i++){
      for (j = 0; j < TD2_rotulos.size(); j++){
        if(TU1_rotulos[i] == TD2_rotulos[j]) {
          codigo1[TU1_end[i]] = TD2_end[j] + fator_correcao2 + codigo1[TU1_end[i]];
        }
      }
    }

    //-----------------------------------------------------------------------
      //Ligar o Codigo 2

    for (i = 0; i < TU2_rotulos.size(); i++){
      for (j = 0; j < TD1_rotulos.size(); j++){
        if(TU2_rotulos[i] == TD1_rotulos[j]) {
          codigo2[TU2_end[i]] = TD1_end[j];
        }
      }
    }

    for (i = 0; i < codigo2.size(); i++){
      switch(codigo2[i]){
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 10: case 11: case 12: case 13:
          i++;
          for (j = 0; j < TU2_end.size(); j++){
            if (i == TU2_end[j])
              flag_check = 1;
          }
          if (flag_check == 0)
            codigo2[i] = codigo2[i] + fator_correcao2;
          flag_check = 0;
          break;

        case 9:   //COPY
          i++;
          for (j = 0; j < TU2_end.size(); j++){
            if (i == TU2_end[j])
              flag_check = 1;
          }
          if (flag_check == 0)
            codigo2[i] = codigo2[i] + fator_correcao2;
          flag_check = 0;

          i++;
          for (j = 0; j < TU2_end.size(); j++){
            if (i == TU2_end[j])
              flag_check = 1;
          }
          if (flag_check == 0)
            codigo2[i] = codigo2[i] + fator_correcao2;
          flag_check = 0;
          break;

        case 14:
          i = codigo2.size();
          break;

        case 15:
          found = i;
          i = codigo2.size();
          codigo2.erase(codigo2.begin() + found);
          break;

        default:
          break;
      }
    }
    //-----------------------------------------------------------------------
    //ALINHAMENTO
    codigo_executavel = codigo1;
    codigo_executavel.insert(codigo_executavel.end(), codigo2.begin(), codigo2.end());

    //-----------------------------------------------------------------------
    //ESCRITA NO ARQUIVO EXECUTAVEL
    ofstream arquivo_executavel (nome_executavel.c_str());
    if (arquivo_executavel.is_open()){
      arquivo_executavel << codigo_executavel[0];
      for (i = 1; i < codigo_executavel.size(); i++)
        arquivo_executavel << " " << codigo_executavel[i];

      arquivo_executavel.close();
    }
    else cout << "Unable to open file";

    //-----------------------------------------------------------------------
    //PRINT
    /*
    cout << "CODIGO 1" << endl;
    cout << endl;
    cout << "TABLE USE" << endl;
    for(j = 0; j < TU1_rotulos.size(); j++)
      cout << TU1_rotulos[j] << " " << TU1_end[j] << endl;

    cout << endl;

    cout << "TABLE DEFINITION" << endl;
    for(j = 0; j < TD1_rotulos.size(); j++)
      cout << TD1_rotulos[j] << " " << TD1_end[j] << endl;

    cout << endl;

    cout << "CODE" << endl;
    for(j = 0; j < codigo1.size(); j++)
      cout << codigo1[j] << " " ;

    cout << endl;
    cout << "-------------------------------------------";
    cout << endl;

    cout << "CODIGO 2" << endl;
    cout << endl;
    cout << "TABLE USE" << endl;
    for(j = 0; j < TU2_rotulos.size(); j++)
      cout << TU2_rotulos[j] << " " << TU2_end[j] << endl;

    cout << endl;

    cout << "TABLE DEFINITION" << endl;
    for(j = 0; j < TD2_rotulos.size(); j++)
      cout << TD2_rotulos[j] << " " << TD2_end[j] << endl;

    cout << endl;

    cout << "CODE" << endl;
    for(j = 0; j < codigo2.size(); j++)
      cout << codigo2[j] << " " ;
    cout << endl;

    cout << "-------------------------------------------";
    cout << endl;
    */
    
    cout << "EXECUTABLE CODE" << endl;
    for(j = 0; j < codigo_executavel.size(); j++)
      cout << codigo_executavel[j] << " " ;
    cout << endl;
  }
  else
    cout << "[Erro] Nao foi possivel ligar os dois modulos. Verifique suas respectivas Tabelas de Uso e Definicao" << endl;

  cout << endl;
  return 0;
}