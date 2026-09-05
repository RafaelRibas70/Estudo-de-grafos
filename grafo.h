#pragma once

void print_matriz(int n, int mat[n][n]){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++){
      printf("%d\t", mat[i][j]);
    }
    printf("\n\n");
  }
}

//a variavel mod é para dizer se o que sera removido é aresta ou é arco
int mod_remove(int n, int mat[n][n], int origem, int destino, int mod){
  if(origem > n){
    return -1;
  }
  if(destino > n){
    return -1;
  }

  //mod = 2 ARCO
  if(mod == 2){
    mat[origem-1][destino-1] = 0;
  }
  //mod = 1 ARESTA
  if(mod == 1){
    mat[origem-1][destino-1] = 0;
    mat[destino-1][origem-1] = 0;
  }

  return 0;
}

int mod_add(int n, int mat[n][n], int origem, int destino, int mod){
  if(origem > n){
    return -1;
  }
  if(destino > n){
    return -1;
  }

  //mod = 2 ARCO
  if(mod == 2){
    mat[origem-1][destino-1] = 1;
  }
  //mod = 1 ARESTA
  if(mod == 1){
    mat[origem-1][destino-1] = 1;
    mat[destino-1][origem-1] = 1;
  }

  return 0;
}
