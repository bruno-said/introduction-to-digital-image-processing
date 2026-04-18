// ===== Bibliotecas =====

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

// ===== FUNÇÕES AUXILIARES =====

// Função auxiliar para normalizar a imagem para o intervalo [0, 255]
cv::Mat normalizeImage(cv::Mat image) {
  // Obtendo o número de linhas e colunas da image
  int rows = image.rows;
  int columns = image.cols;

  // Obtendo o valor máximo e mínimo da imagem
  uint8_t maximum = 0;
  uint8_t minimum = 255;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      uint8_t value = image.at<uint8_t>(i, j);
      maximum = std::max(value, maximum);
      minimum = std::min(value, minimum);
    }
  }

  // Criando uma imagem para ser retornanda
  cv::Mat returnImage(rows, columns, CV_8UC1);

  // Executando a normalização proporcinal
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      uint8_t oldValue = image.at<uint8_t>(i, j);
      uint8_t newValue = ((oldValue - minimum) / (maximum - minimum)) * 255;
      returnImage.at<uint8_t>(i, j) = newValue;
    }
  }

  // Rotornando o resultado
  return returnImage;
}

// ===== FUNÇÃO PRINCIPAL =====

int main(int argc, char** argv) {
  // Carregando a imagem original
  cv::Mat inputImage = cv::imread("./images/100-dollars.tif", cv::IMREAD_GRAYSCALE);

  // Verificando se a imagem foi carregada com sucesso
  if (inputImage.empty()) {
      std::cout << "Nao conseguiu abrir ou carregar a imagem" << std::endl;
      return -1;
  }

  // Obtendo o número de linhas e colunas da image
  int rows = inputImage.rows; // Altura
  int columns = inputImage.cols; // Largura

  // Criando uma image de saída
  cv::Mat outputImage(rows, columns, CV_8UC1);

  // Executando o loop para cara camada, ou seja, cada bit
  for (int i = 0; i < 8; i++) {
    // Criando a imagem de saída para a i-esima camada 
    for (int j = 0; j < rows; j++) {
      for (int k = 0; k < columns; k++) {
        uint8_t mask = 1 << i; // Másca da camada
        uint8_t value = inputImage.at<uchar>(j, k); // Valor do pixel
        outputImage.at<uchar>(j, k) = mask & value; // Operação de bitwase
      }
    }

    // Nomalizando imagem de saída
    outputImage = normalizeImage(outputImage).clone();

    // Salvando a imagem no disco
    bool success = cv::imwrite("./images/image-" + std::to_string(i) + ".png", outputImage);
  }

  return 0;
}

