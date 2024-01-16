# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I./src/header
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
FILE_DIR = ./files
HEADERS = ./src/header/*.h

# Cibles par défaut
all: directories

# Création des répertoires
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(FILE_DIR)

# Règle générique pour compiler l'exemple arbreBinaireSimple
$(BIN_DIR)/arbreBinaireSimple: $(OBJ_DIR)/arbre.o $(OBJ_DIR)/arbreBinaireSimple.o $(OBJ_DIR)/file.o $(OBJ_DIR)/affichageArbre.o 
	$(CC) $^ -o $@

# Règle générique pour compiler l'exemple arbreBinaireRecherche
$(BIN_DIR)/arbreBinaireRecherche: $(OBJ_DIR)/arbre.o $(OBJ_DIR)/arbreBinaireRecherche.o $(OBJ_DIR)/file.o $(OBJ_DIR)/affichageArbre.o 
	$(CC) $^ -o $@

# Règle générique pour compiler l'exemple arbreBinaireRecherche
$(BIN_DIR)/arbreAVL: $(OBJ_DIR)/arbre.o $(OBJ_DIR)/arbreAVL.o $(OBJ_DIR)/affichageArbre.o 
	$(CC) $^ -o $@


# Règle générique pour les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour arbre Binaire Simple
arbreBinaireSimple: directories
	$(MAKE) $(BIN_DIR)/arbreBinaireSimple
	$(BIN_DIR)/arbreBinaireSimple

# Règle pour arbre Binaire Recherche
arbreBinaireRecherche: directories
	$(MAKE) $(BIN_DIR)/arbreBinaireRecherche
	$(BIN_DIR)/arbreBinaireRecherche
	
# Règle pour arbre AVL
arbreAVL: directories
	$(MAKE) $(BIN_DIR)/arbreAVL
	$(BIN_DIR)/arbreAVL


# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Règle pour nettoyer les fichiers de temps générés
cleanfiles:
	rm -rf $(FILE_DIR)/*

.PHONY: all clean cleanfiles arbreBinaireSimple directories
