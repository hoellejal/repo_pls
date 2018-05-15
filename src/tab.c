int* table_pourcentage_huffman(char const* file_name){ //Recoit le nom du fichier a compresser (argv[1]) et renvoie un tableau a 256 cases des occurences des caractères
  FILE* f = fopen(file_name, "r");
  if (!f) {
    printf("Ouverture du fichier impossible. Abandon.\n");
    exit(0);
  }
  int* table = malloc(256 * sizeof(int));
  for (int i = 0; i < 256; i++) {
    table[i] = 0;
  }
  char c;
  while ((c = fgetc(f)) != EOF) {
    table[c]++;
  }
  fclose(f);
 
  return table;
}

table_l_code* creer_table_arbre(pnoeud_t racine){
  table_l_code* tab = malloc(256*sizeof(4*uint64+int+char));
  pnoeud_t bl = racine;
  save = tab;
  int i=0;
  while(bl!=NULL){
    while((bl->fgauche!=NULL)&&(bl->fdroit!=NULL)){
      if(bl->fdroit != NULL){
        bl = bl->fdroit;
      }
      else if (bl->fgauche!=NULL){
        bl = bl->fgauche;
      }
      i++;
    }
    tab[i]->symbole=bl->c;
    //et pour le reste idk
  }
  return save;
}
