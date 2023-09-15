ref = 40 45 46 47 48 49 54 55 61 62
test:
	g++ -Wall -Werror -std=c++17 -g *.cpp *.h -o lab4
	./lab4 in40.txt > ans.txt && diff out40.txt ans.txt
	./lab4 in45.txt > ans.txt && diff out45.txt ans.txt
	./lab4 in46.txt > ans.txt && diff out46.txt ans.txt
	./lab4 in47.txt > ans.txt && diff out47.txt ans.txt
	./lab4 in48.txt > ans.txt && diff out48.txt ans.txt
	./lab4 in49.txt > ans.txt && diff out49.txt ans.txt
	./lab4 in54.txt > ans.txt && diff out54.txt ans.txt
	./lab4 in55.txt > ans.txt && diff out55.txt ans.txt
	./lab4 in61.txt > ans.txt && diff out61.txt ans.txt
	./lab4 in62.txt > ans.txt && diff out62.txt ans.txt

testloop:
	./lab4 in$(ref).txt > ans$(ref).txt && diff out$(ref).txt ans$(ref).txt

	a = 0; \
	while [ $(a) -le 100 ] ; do \
		ifneq ["in$(a).txt",""]; then \
			./lab4 in$(a) > ans$(a) && diff out*.txt ans.txt; \
		fi \
		((a = a+1)); \
	done; \
