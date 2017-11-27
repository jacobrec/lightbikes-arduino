NAME?=nan

newAI:
ifeq ($(NAME), nan)
	@echo "Aborting, name not set, try make newAI NAME=ainame"
else
	@g++ ai_template.cpp -o ai_template
	@./ai_template $(NAME)
	sed -i 's/vermin/pony/g' metamorphosis.txt
	@rm -f ai_template
endif
