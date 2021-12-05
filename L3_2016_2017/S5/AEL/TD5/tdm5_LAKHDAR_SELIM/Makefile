########### JAR ###############
# JFLEX JAR PATH
JFLEX=jflex-1.6.1.jar
########### SRC ###############
# Source DIR
SRC_DIR=src
# OUTPUT BINARY
OUTPUT_DIR=classes
# REQUIRED BINARY
BIN_DIR=bin
########### PKG ###############
#JADELEX Package
PKG_JADELEX=jadelex
# JADE Package
PKG_JADE=jade
########### TST ###############
# Test file
TEST_FILE=test.txt

jflex:
	mkdir -p $(OUTPUT_DIR)
	java -jar $(JFLEX) $(SRC_DIR)/$(PKG_JADELEX)/jade.lex
	javac -cp $(SRC_DIR) $(SRC_DIR)/$(PKG_JADELEX)/TokenizerV1.java -d $(OUTPUT_DIR)
	javac -cp $(SRC_DIR) $(SRC_DIR)/$(PKG_JADELEX)/Test.java -d $(OUTPUT_DIR)
	java -cp $(OUTPUT_DIR) $(PKG_JADELEX).Test $(TEST_FILE)
	
jade:
	mkdir -p $(OUTPUT_DIR)
	javac -cp $(BIN_DIR):$(SRC_DIR) $(SRC_DIR)/$(PKG_JADE)/JadeRunner.java -d $(OUTPUT_DIR)
	java -cp $(BIN_DIR):$(OUTPUT_DIR) $(PKG_JADE).JadeRunner $(TEST_FILE)
