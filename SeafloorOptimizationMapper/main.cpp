#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

int main(int argc, char *argv[]) 
{    
    system("curl -s http://abilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt -o prolab1.txt");

    FILE *filep;
    int rowDraw;
    int numbers[100];
    int numbersCount = 0;

    if (filep = fopen("prolab1.txt", "r")) 
	{
        int row = 1;
        char line[256];

        while (fgets(line, sizeof(line), filep) != NULL) 
		{
            printf("%s", line);
            row++;
        }

        fclose(filep);
        
        printf("\nWhich row do you want the coordinates to be plotted: ");
        scanf("%d", &rowDraw);
        
        filep = fopen("prolab1.txt", "r");
        row = 1;
		
        while (fgets(line, sizeof(line), filep) != NULL) 
		{
            if (row == rowDraw) 
			{
				char *mark = strtok(line, "()");
            
				while (mark != NULL) 
				{
                    int x, y;
                    
					if (sscanf(mark, "%d,%d", &x, &y) == 2) 
					{
                        numbers[numbersCount++] = x;
                        numbers[numbersCount++] = y;
                    }
                    
					mark = strtok(NULL, "()");
                }
                break; 
            }
            row++;
        }
        fclose(filep);        
    }
    
	 else 
	{
        printf("File could not be opened, a problem occured.\n");
    }
    
    initwindow(1500,1500);
    
    setbkcolor(15);
	cleardevice();
	
	int factor=10;	
	int screenWidth = getmaxx();
	int screenHeight =getmaxy();
	int squareSize =10;
	int squareCount=0;
	int a,b,c,d,i,j,x,y,k,l;
	
	setlinestyle(0,0,0);
	setcolor(7);
	
		for(a = 0; a<screenWidth; a +=squareSize)
		{
			for(b=0 ; b <screenHeight; b +=squareSize)
			{
				rectangle(a , b, a +squareSize, b+ squareSize);		
			}
		}
		
		setcolor(0);
		setlinestyle(0,0,0);
		
		for (a = 0; a < numbersCount; a += 2) 
		{
            numbers[a] *= factor;
            numbers[a + 1] *= factor;
        }
        		
        int flag=0;
        int tmp[256]; 
        int tmp3[256][256];
       	double area=0.0;
       	double totalArea=0.0;
        int areaCount;
        int count;
        int shapeCount=0;
		b=0;
		
		for(i=0;i<numbersCount;i+=2)
		{	
			for(j=1;j<numbersCount;j+=2)
			{
				flag++;
			
				if(numbers[i]==numbers[j+1] && numbers[i+1]==numbers[j+2])
				{
					shapeCount++;					
					for(a=0; a < (flag*2)+2 ;a++)
					{	
						tmp[a]=numbers[b];
						b++;
					}
					
					count=a;
					flag=0;
					
					for (x = 0; x < numbersCount; x += 2) 
					{
            			tmp[x] /= factor;
            			tmp[x + 1] /= factor;
        			}
        			
						for (y = 0; y < count -2 ; y += 2) 
					{
                		area += (tmp[y] * tmp[y + 3]) - (tmp[y + 2] * tmp[y + 1]);
            		}
					 
					  area = abs(area) / 2;
					  totalArea +=area;
					  
					  for (x = 0; x < numbersCount; x += 2) 
					{
            			tmp[x] *= factor;
            			tmp[x + 1] *= factor;
        			}
					
					int minx=tmp[0];
					int maxx=tmp[0];
					int miny=tmp[1];
					int maxy=tmp[1];
				
					for (i = 0; i < count ; i+=2) 
					{
        				if (tmp[i] < minx) 
						{
            				minx = tmp[i];
        				}
        				
        				if (tmp[i] > maxx) 
						{
            				maxx =tmp[i];
        				}
        				
					}
					
					for(i = 1; i< count ; i+=2)
					{
						if (tmp[i] < miny) 
						{
            				miny = tmp[i];
        				}
        					
        				if (tmp[i] > maxy) 
						{
            				maxy = tmp[i];
        				}
					}
					
					tmp3[shapeCount-1][0]=minx;
					tmp3[shapeCount-1][1]=maxx;
					tmp3[shapeCount-1][2]=miny;
					tmp3[shapeCount-1][3]=maxy;
					
					setfillstyle(1,8);
					drawpoly(count/2,tmp);
					fillpoly(count/2,tmp);
					memset(tmp,0,sizeof(tmp));
					i=b;
					j=b+1-(2);
				}
				area=0.0;	
			}
			
			printf("Area of shape %.2lf\n",totalArea);
		}
		
		double resourceReserveValue=(totalArea *10);
		int unitDrillingCost;
		double unitPlatformCost;
		
		printf("Total reserve value amount %.2lf \n",resourceReserveValue);
		printf("Please enter unit drilling cost:");
		scanf("%d",&unitDrillingCost);
		printf("Please enter unit platform cost:");
		scanf("%lf",&unitPlatformCost);
		
		delay(3000);
		
		cleardevice();
		setbkcolor(15);
		setcolor(7);
		
		for(a = 0; a<screenWidth; a +=squareSize)
		{
			for(b=0 ; b <screenHeight; b +=squareSize)
			{
				rectangle(a , b, a +squareSize, b+ squareSize);		
			}
		}
		
		setcolor(4);
		setlinestyle(0,0,0);
		b=0;
		flag=0;
		
		for(i=0;i<numbersCount;i+=2)
		{
			for(j=1;j<numbersCount;j+=2)
			{
				flag++;
			
				if(numbers[i]==numbers[j+1] && numbers[i+1]==numbers[j+2])
				{
					for(a=0; a < (flag*2)+2 ;a++) 
					{	
						tmp[a]=numbers[b];
						b++;
					}
					
					count=a;
					flag=0;
					
					setfillstyle(1,8);
					drawpoly(count/2,tmp);
					memset(tmp,0,sizeof(tmp));
					i=b;
					j=b+1-(2);
				}
				
			}
			
		}
		
		delay(3000);
	
		int xStep=(40/(unitDrillingCost)) ,yStep=(40/(unitDrillingCost));
		int numberSquarePainted=0;
		setcolor(0);
		
		for(a = 0 ; a <shapeCount ;a ++)
		{
			for ( x = tmp3[a][0]; x < tmp3[a][1]; x += xStep) 
			{
        		for ( y = tmp3[a][2]; y < tmp3[a][3]; y += yStep) 
				{
					rectangle(x , y, x +xStep, y+ yStep);
										  
					int foundPixel = 0; 
    				
    				for ( k = x; k < tmp3[a][1]; k+=xStep) 
					{
        				for ( l = y; l <  tmp3[a][3]; l+=yStep) 
						{
            				int pixelColor = getpixel(k, l);
		            	
            				if (pixelColor ==4  )  
							{
                				foundPixel = 1;
                				break;
            				}
        				}
        		
        				if (foundPixel) 
						{
							setfillstyle(0,5);
        			
        					for ( c = x + 1; c < x + xStep; c++) 
							{
        						for ( d = y + 1; d < y + yStep; d++) 
								{
            						putpixel(c, d, 5);
        						}
    						}
							
							numberSquarePainted++;
							break; 
        				}
        		
    				}
					
        		}
        		
    		}
		
		}
		
		int totalPlatform= numberSquarePainted;
		int totalDrilling= numberSquarePainted;
		double totalPlatformCost= (numberSquarePainted * unitPlatformCost);
		int totalDrillingCost= (numberSquarePainted * unitDrillingCost);
		double totalCost = (totalDrillingCost + totalPlatformCost);
		double  profit=(resourceReserveValue - totalCost);
		
		printf("Total number of platform :%d\n",totalPlatform);
		printf("Total number of drilling :%d\n",totalDrilling);
		printf("Total platform cost :%.2lf\n",totalPlatformCost);
		printf("Total drilling cost :%d\n",totalDrillingCost);
		printf("Total cost :%.2lf\n",totalCost);
		printf("Profit :%.2lf\n",profit);
		
		getch();
		closegraph();

    	return 0;
}
