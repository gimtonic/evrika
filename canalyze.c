#include <stdio.h>
#include <regex.h>
#include <string.h>

#define FIND_LINE "\\{" 

int main(int argc, char **argv)
{
   // Переменная, в которую будет помещен указатель на созданный
   // поток данных 
    FILE *f;
   
   // Переменная, в которую поочередно будут помещаться считываемые строки
    char str[500], functionName[100] ;

   char *name[100];
   //Указатель, в который будет помещен адрес массива, в который считана 
   // строка,или NULL если достигнут коней файла или произошла ошибка
    char *line;   

    regex_t preg,preg2;
    int err,err2,regerr,regerr2;
    regmatch_t pm;

    int a,b,j,count,n;
   n=0;
    err = regcomp (&preg, FIND_LINE, REG_EXTENDED);
  //  if (err != 0) {
  //      char buff[512];
  //      regerror(err, &preg, buff, sizeof(buff));
  //      printf("%s",buff);
  //  }
	
    if (argc < 2) {
        printf ("%s%s","Используйте команду \n\n","./canalyze <имя файла>\n\n");
        return 1;
    }
  
   // Открытие файла с режимом доступа «только чтение» и привязка к нему 
   // потока данных
    f = fopen(argv[1],"r");

   // Проверка открытия файла
   if (f == NULL) {

	printf ("Ошибка открытия файла\n");
	return 1;
  
   } else {
	
	printf("Detected functions / call times:\n");
	
	//Чтение (построчно) данных из файла в бесконечном цикле
        while (1) {

	// Чтение одной строки  из файла
        line = fgets (str,sizeof(str),f);
        //Проверка на конец файла или ошибку чтения
        if (line == NULL)
        {
         // Проверяем, что именно произошло: кончился файл
         // или это ошибка чтения
         if ( feof (f) != 0)
         {
            //Если файл закончился, выводим сообщение о завершении 
            //чтения и выходим из бесконечного цикла
            printf ("\nЧтение файла закончено\n");
            break;
         }
         else
         {
            //Если при чтении произошла ошибка, выводим сообщение 
            //об ошибке и выходим из бесконечного цикла
            printf ("\nОшибка чтения из файла\n");
            break;
         }
     }
      //Если файл не закончился, и не было ошибки чтения 
      //выводим считанную строку  на экран
    regerr = regexec (&preg, str, 0, &pm, 0);
    j=0;
    count=0;

    if (regerr == 0) { 
	
	for(int i=0; i<= sizeof(str); i++) {
		if (str[i] == ' ') { 
		a = i;
		//printf("%d\n",a);
		break;
	        }
	}

        for(int i=0; i<= sizeof(str); i++) {
                if (str[i] == '(') {
                b = i;
                //printf("%d\n",b);
                break;
                }
        }	
	for(int i=0; i<=sizeof(str); i++) {
 		
		if ((i>a)&&(i<b)) {
         
		functionName[j] = str[i];
		j++;
       		}
	}
		
 //       printf("%s: called %d times\n",functionName,3);

	name[n] = functionName;
	printf("%sbbbb",name[n]);
	n++;
}
}

	
   }

   // Закрываем файл
   printf ("Закрытие файла: ");
   if ( fclose (f) == EOF) printf ("ошибка\n");
   else printf ("выполнено\n");	 
   return 0;

}

