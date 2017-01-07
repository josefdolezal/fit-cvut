CC=swiftc
TARGETS=main
FILES=CBridge.swift BotController.swift Bot.swift BotServer.swift Logger.swift StringExtensions.swift main.swift

all: $(TARGETS)

main: main.swift
	$(CC) -o main $(FILES)

deploy:
	cat $(FILES) > merge.swift

clean:
	rm -f $(TARGETS)
