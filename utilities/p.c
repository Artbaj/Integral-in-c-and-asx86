
#include <unistd.h>  // dla lseek, STDIN_FILENO
#include <fcntl.h>   // dla SEEK_SET
#include <x86intrin.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
extern uint16_t get_fpu_control_word(void);
//extern uint16_t get_status(void);

extern void change_precision(void);
extern unsigned long long miernik(void);
#include <stdio.h>
#include <stdint.h>
typedef struct {
    int exponent;
    double coefficient;
}Term;

typedef struct{
    Term *terms;
    int capacity;
    int size;
}Polynomial;


extern double riemannSum(double x,double coefficient,int exp);
extern unsigned long long miernik(void);
void init_poly(Polynomial* p);
int compare_terms(const void *a, const void *b);
void print_poly_array(Polynomial *p); 
void add_term_array(Polynomial *p, int exp, double coeff); 
double poly_eval(Polynomial* p,double x);
double integrate(Polynomial* p,double start,double end,long double step);
void testing(double X,double coefficient, int power);


int main() 
{
    double startI,endI,coefficient;
    long double step;
    int exponent;
    int count = 1;
    Polynomial p;
    init_poly(&p);
    testing(0.2,2.,2);
    do{
        printf("Provide an coefficient [0 if u are done]\n");
        scanf("%lf",&coefficient);
        if(!coefficient) continue;
        printf("Provide an exponent\n");
        scanf("%d",&exponent);
        add_term_array(&p,exponent,coefficient);
        count++;
       
    }
    while(coefficient);
   

    print_poly_array(&p);
    printf("state starting point ending point and step size\n");
    scanf("%lf %lf %Lf",&startI,&endI,&step);
   
    FILE *plik = fopen("time.txt","w");
    double resoult;
    unsigned long long average =0;
    for(int i=0;i<100;i++){
       unsigned long long start = miernik(); 
      resoult =  integrate(&p,startI,endI,step);
       average+= miernik()-start;
    }
   clock_t t = clock();
    
    for(int i = 0; i < 100; i++) resoult =  integrate(&p,startI,endI,step);

    
    t = clock() - t;
    double avg_ms = ((double)t / CLOCKS_PER_SEC) * 100.0 / 100.0;

    printf("y = ");
    print_poly_array(&p);
    printf("dla x E <%lf , %lf> Sy(x) = %lf\n",startI,endI,resoult);
    printf("Takes on average %llu cycles\ntakes on average:%lf ms\n",average/100,avg_ms);
    return 0;



}
void init_poly(Polynomial *p) {
    p->size = 0;
    p->capacity = 10;
    p->terms = malloc(p->capacity * sizeof(Term));
}

void add_term_array(Polynomial *p, int exp, double coeff) {
    for (size_t i = 0; i < p->size; i++) {
        
        if (p->terms[i].exponent == exp) {
            p->terms[i].coefficient += coeff;
            return;
        }
    }

    if (p->size >= p->capacity) {
        p->capacity *= 2;
        p->terms = realloc(p->terms, p->capacity * sizeof(Term));
    }

    p->terms[p->size].exponent = exp;
    p->terms[p->size].coefficient = coeff;
    p->size++;
}


int compare_terms(const void *a, const void *b) {
    Term *termA = (Term *)a;
    Term *termB = (Term *)b;
    return (termB->exponent - termA->exponent);

}


void print_poly_array(Polynomial *p) {
    qsort(p->terms, p->size, sizeof(Term), compare_terms);
    for (size_t i = 0; i < p->size; i++) {
        if (p->terms[i].coefficient != 0) // Pomijamy zera
            if(!p->terms[i].exponent) printf("%+.1f", p->terms[i].coefficient);
            else printf("%+.1fx^%d ", p->terms[i].coefficient, p->terms[i].exponent);
    }
    printf("\n");
}

double integrate(Polynomial* p,double start,double end,long double step){
    double area =0;
    int stepAmt = (int)(end-start)/step;
    double pos = start;
    for(int i=0; i<stepAmt;i++){
        pos +=step;
        for(size_t j =0;j<p->size;j++){
           area+=riemannSum(pos,p->terms[j].coefficient,p->terms[j].exponent);
        }
        }
        area*=step;
    return area;
}
void testing(double X,double coefficient,int power){
    printf("%lf\n",riemannSum(X,coefficient,power));//zmienic calkowicie na assembly i przez wskaznik
} 
