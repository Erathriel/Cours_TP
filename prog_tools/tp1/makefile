JAVAC = javac
SRC = ./src
BIN = ./bin
JAVADOC = javadoc
DOC = ./doc
JUNIT = ./libs/junit-4.12.jar:./libs/hamcrest-core-1.3.jar
JAVA=java
TESTS=tests.testAccount tests.testATM
MOCKITO=./libs/mockito-core-2.10.0.jar:./libs/byte-buddy-1.7.5.jar:./libs/byte-buddy-agent-1.7.5.jar:./libs/objenesis-2.6.jar
JACOCO_AGENT=./libs/jacocoagent.jar
REPORT=./reports
JACOCO_CLI=./libs/jacococli.jar

appli :
	$(JAVAC) -d $(BIN) $(SRC)/appli/fr/ufc/l3info/oprog/*.java
tests :
	$(JAVAC) -cp $(BIN):$(JUNIT):$(MOCKITO) -d $(BIN) $(SRC)/tests/*.java
runtests :
	$(JAVA) -cp $(BIN):$(JUNIT):$(MOCKITO) org.junit.runner.JUnitCore $(TESTS) 
docs : 
	$(JAVADOC) -d $(DOC) $(SRC)/appli/fr/ufc/l3info/oprog/*.java
report :
	$(JAVA) -javaagent:$(JACOCO_AGENT)=destfile=$(REPORT)/jacoco.exec -cp $(BIN):$(JUNIT):$(MOCKITO) org.junit.runner.JUnitCore $(TESTS)
coverage :
	$(JAVA) -jar $(JACOCO_CLI) report $(REPORT)/jacoco.exec --sourcefiles $(SRC)/appli/ --classfiles $(BIN) --html $(REPORT)/html 
