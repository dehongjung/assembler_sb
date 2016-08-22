# Montador e Ligador - Assembler and Linker

  Universidade de Brasilia
  Departamento de Ciencia da Computacao
  Basic Software
  Project: Assembler and Linker
  Authors: De Hong Jung (eu.dehong@gmail.com) and Camila Brito (camila.gdebrito@gmail.com)

## Description
	This repository contains the code of a project for the course of Basic Software at University of Brasília. This work consists in developing an assembler of an invented Assembly code and generate an object file, besides of detecting all the lexicon, semantic and syntatic error. Furthermore, this work asks for a linker that link two object files generated by the assembler and generate an executable file in the end.

## Tools
	- Operating System: Ubuntu 14.04 64 bits
	- Language: C++
	- Compiler: g++ (Ubuntu 4.8.2-19ubuntu1) 4.8.2
	- IDE: Sublime Text 3

## Compilation
		Assembler: 
			$ g++ assembler.cpp -o assembler

		Linker: 
			$ g++ linker.cpp -o linker

## Execution
		Assembler: 
			$ ./assembler <name_asm_file> <name_object_file>

		Linker:
			$ ./linker <name_first_object> <name_second_object> <name_executable_file>

## Simulation
	In order to simulate the executable file generated, an simulator provided by the discipline professor was used.

	- Allow access:
		$ chmod +x simulador

	- Execution:
		$ ./simulador <name_executable_file>.e
