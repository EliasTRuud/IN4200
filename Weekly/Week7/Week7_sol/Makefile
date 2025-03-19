.PHONEY: clean notes

notes:
	pandoc -o notes.pdf notes.md
	xdg-open notes.pdf

clean:
	@rm -f *.o *.out $(PROGRAMS)
