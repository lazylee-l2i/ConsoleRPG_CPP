#include "StartScreen.h"

void show_start_screen()
{
    std::list<std::string> loding_screen;
    std::string screen1 = R"(
                .+####################-                         
            .-###-..........-+####-.                
            -+#-.         .-#+##+.-     +#####+++##+ +#### .  -  ###++++-       ###-                 
            --.           .+#++#+.     .+###.  .+#+ -###+       ###-.+###      ####                 
                        .+#++#-.       .+###.  .-++ -###+       ###- .+###    ## ##-                    
                        .-+#++#-       .+###.       -###+       ###- .-+##   +#  ###                    
                        .-####+.       .+###++++-   -###+       ###-  .+##   #+  ###-                   
                      .+##+#+.         .+###++#+-   -###+    -  ###-  .+##  ##-  ####                   
                    .+####+.           .+###. -+-++ -###+   ++  ###- .-###  ####+####.                  
                  -+#+##-              .+###.  .-#+ -###+  -#+  ###- .+### ##-  .+####                  
                -#+-++-                .+###. .-+#+ -###+ -+#+  ###-.+### .##.   -####.                 
              .-#++#+.                .-+###++++##+ +###+++##+  ###+##    ##+-  .-#####-.               
             .+#+##+           .-#+-               
           -+####+...........+##+.                                                                
        .-+####################.    
)";
    /*std::string screen5 = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    loding_screen.push_back(screen1);
    loding_screen.push_back(screen2);
    loding_screen.push_back(screen3);
    loding_screen.push_back(screen4);
    loding_screen.push_back(screen5);
    loding_screen.push_back(screen4);
    loding_screen.push_back(screen3);
    loding_screen.push_back(screen2);*/
    
    std::list<std::string>::iterator cur = loding_screen.begin();


    auto iter = loding_screen.begin();
    int n = 0;
    while (n != 10)
    {
        std::cout << (*iter) << std::endl;
        Sleep(1000);
        system("cls");
        iter++;
        if (iter == loding_screen.end())
        {
            iter = loding_screen.begin();
        }
        n++;
    }

}
