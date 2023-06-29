FROM lordmilko/i686-elf-tools

WORKDIR /home/user/



COPY . .

ENTRYPOINT ["sh","build.sh"]