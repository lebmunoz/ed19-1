// Copyright [2019] Luis Enrique Borba Munoz & Ricardo Luiz Camargo Prado

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include "Xml.h"
#include "Sweeper.h"

using namespace std;

int main() {

    Xml *xml = new Xml();

    // Laço para rodar o programa passando todos os nomes dos arquivos para a entrada;
    for (int j = 1; j <= 8; ++j) {
        // Monta na variável "file" o caminho (path) do arquivo a ser lido;
        string file = "../dataset0" + std::to_string(j) + ".xml";
        // Apenas imprime na tela qual o arquivo sendo lido atualmente;
        cout << "Parsing " << file.c_str() << endl;
        // Cria uma instância da classe que vai fazer a verificação das imagens atrás de componentes conexos;
        Sweeper * pSweeper =  new Sweeper();
        // Este condicional vai verificar se o "parse" do arquivo xml foi concluído corretamente (se a estrutura
        // xml está correta) e vai iniciar a varredura da imagem;
        if (xml->parse(file.c_str())) {
            // Esta variável coloca em um vetor todos os nodos que possuem a
            // tag "img" através do método "getNodesByName";
            auto imgNodes = xml->getNodesByName("img");

            // Este laço percorre todas as imagens que estão armazenadas na variável imgNodes e passa para o método
            // "calculate" identificar os componentes conexos;
            for (int i = 0; i < imgNodes.size(); i++) {
                // Esta variável pega o endereço de cada imagem individualmente no vetor;
                auto image = imgNodes.at(i);
                // Neste comando de impressão no console, a saída está formatada corretamente, com os textos pedidos
                // pelo teste automático e chamando o método "calculate" para cada imagem do vetor "imgNodes";
                cout << "Imagem: " <<
                image->getNodeByName("name")->getValue() << " " <<
                "Componentes:" << pSweeper->calculate(image) << endl;
            }
        } else {
            // Mensagem de erro caso o arquivo xml possua erro de formatação;
            cout << "error" << endl;
        }
    }
}

