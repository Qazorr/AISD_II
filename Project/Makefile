compile:
	@g++ Graph.cpp -o Graph.x

file = ska0

test: clean compile
	@./Graph.x < testy/$(file).in
	@cat testy/$(file).out
test1: clean compile
	@./Graph.x < testy/ska1.in
	@cat testy/ska1.out
tester: clean
	@g++ -std=c++17 tester.cpp -o tester.x
	@./tester.x

clean:
	@rm -f *.x