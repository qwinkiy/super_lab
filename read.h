void read_file(){
    char buffer[256];
    FILE * f = fopen("input.txt","r");
    if(f){
        while((fgets(buffer, 256, f))!=NULL){
            struct command a = parse_command(buffer);
                if (a.command != -1){
                    printf("command %i\n",a.command);
                    printf("fileds %s\n",a.fileds);
                    printf("fil_len %i\n",a.fil_len);
                    printf("cond %s\n",a.cond);
                    printf("con_len %i\n",a.con_len);
                    printf("конец\n");
                    // вызов команд
            }
        }
        fclose(f);
    }
}