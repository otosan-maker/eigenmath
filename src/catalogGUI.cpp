#include <fxcg/display.h>
#include <fxcg/file.h>
#include <fxcg/keyboard.h>
#include <fxcg/system.h>
#include <fxcg/misc.h>
#include <fxcg/app.h>
#include <fxcg/serial.h>
#include <fxcg/rtc.h>
#include <fxcg/heap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "menuGUI.hpp"
#include "catalogGUI.hpp"

catalogFunc completeCat[CAT_COMPLETE_COUNT] = { // list of all functions (including some not in any category)
  {"abs(x)", "abs(", "", CAT_CATEGORY_LINEARALG},
  {"adj(m)", "adj(", "", CAT_CATEGORY_LINEARALG},
  {"and(a,b,...)", "and(", "", CAT_CATEGORY_PROG},
  {"arccos(x)", "arccos(", "", CAT_CATEGORY_TRIG},
  {"arccosh(x)", "arccosh(", "", CAT_CATEGORY_TRIG},
  {"arcsin(x)", "arcsin(", "", CAT_CATEGORY_TRIG},
  {"arcsinh(x)", "arcsinh(", "", CAT_CATEGORY_TRIG},
  {"arctan(x)", "arctanh(", "", CAT_CATEGORY_TRIG},
  {"arg(z)", "arg(", "", CAT_CATEGORY_COMPLEXNUM},
  {"besselj(x,n)", "besselj(", "", CAT_CATEGORY_SPECIAL},
  {"binding(x)", "binding(", "", CAT_CATEGORY_OTHER},
  {"binomial(n,k)", "binomial(", "", CAT_CATEGORY_POLYNOMIAL},
  {"ceiling(x)", "ceiling(", "", CAT_CATEGORY_OTHER},
  {"check(x)", "check(", "", CAT_CATEGORY_PROG},
  {"choose(n,k)", "choose(", "", CAT_CATEGORY_OTHER},
  {"circexp(x)", "circexp(", "", CAT_CATEGORY_CALCULUS},
  {"clock(z)", "clock(", "", CAT_CATEGORY_COMPLEXNUM},
  {"coeff(p,x,n)", "coeff(", "", CAT_CATEGORY_LINEARALG},
  {"cofactor(m,i,j)", "cofactor(", "", CAT_CATEGORY_LINEARALG},
  {"condense(x)", "condense(", "", CAT_CATEGORY_OTHER},
  {"conj(z)", "conj(", "", CAT_CATEGORY_COMPLEXNUM},
  {"contract(a,i,j)", "contract(", "", CAT_CATEGORY_LINEARALG},
  {"cos(x)", "cos(", "", CAT_CATEGORY_TRIG},
  {"cosh(x)", "cosh(", "", CAT_CATEGORY_TRIG},
  {"cross(u,v)", "cross(", "", CAT_CATEGORY_LINEARALG},
  {"curl(u)", "curl(", "", CAT_CATEGORY_LINEARALG},
  {"d(f,x)", "d(", "", CAT_CATEGORY_CALCULUS},
  {"defint(f,x,a,b)", "defint(", "", CAT_CATEGORY_CALCULUS},
  {"deg(p,x)", "deg(", "", CAT_CATEGORY_POLYNOMIAL},
  {"denominator(x)", "denominator(", "", CAT_CATEGORY_OTHER},
  {"det(m)", "det(", "", CAT_CATEGORY_LINEARALG},
  {"dim(a,n)", "dim(", "", CAT_CATEGORY_LINEARALG},
  {"dirac(x)", "dirac(", "", CAT_CATEGORY_OTHER},
  {"divisors(x)", "divisors(", "", CAT_CATEGORY_CALCULUS},
  {"do(a,b,...)", "do(", "", CAT_CATEGORY_PROG},
  {"dot(a,b,...)", "dot(", "", CAT_CATEGORY_LINEARALG},
  {"eigen(m)", "eigen(", "", CAT_CATEGORY_LINEARALG},
  {"eigenval(m)", "eigenval(", "", CAT_CATEGORY_LINEARALG},
  {"eigenvec(m)", "eigenvec(", "", CAT_CATEGORY_LINEARALG},
  {"erf(x)", "erf(", "", CAT_CATEGORY_OTHER},
  {"erfc(x)", "erfc(", "", CAT_CATEGORY_OTHER},
  {"eval(f,x,a)", "eval(", "", CAT_CATEGORY_CALCULUS},
  {"exp(x)", "exp(", "", CAT_CATEGORY_OTHER},
  {"expand(r,x)", "expand(", "", CAT_CATEGORY_POLYNOMIAL},
  {"expcos(x)", "expcos(", "", CAT_CATEGORY_TRIG},
  {"expsin(x)", "expsin(", "", CAT_CATEGORY_TRIG},
  {"factor(p,x)", "factor(", "", CAT_CATEGORY_POLYNOMIAL},
  {"factorial(x) / x!", "!", "", CAT_CATEGORY_OTHER},
  {"filter(f,a,b,...)", "filter(", "", CAT_CATEGORY_PROG},
  {"float(x)", "float(", "", CAT_CATEGORY_OTHER},
  {"floor(x)", "floor(", "", CAT_CATEGORY_OTHER},
  {"for(i,j,k,a,b,...)", "for(", "", CAT_CATEGORY_PROG},
  {"gcd(a,b,...)", "gcd(", "", CAT_CATEGORY_CALCULUS},
  {"hermite(x,n)", "hermite(", "", CAT_CATEGORY_SPECIAL},
  {"hilbert(n)", "hilbert(", "", CAT_CATEGORY_LINEARALG},
  {"imag(z)", "imag(", "", CAT_CATEGORY_COMPLEXNUM},
  {"integral(f,x)", "integral(", "", CAT_CATEGORY_CALCULUS},
  {"inv(m)", "inv(", "", CAT_CATEGORY_LINEARALG},
  {"isinteger(x)", "isinteger(", "", CAT_CATEGORY_PROG},
  {"isprime(n)", "isprime(", "", CAT_CATEGORY_CALCULUS},
  {"laguerre(x,n,a)", "laguerre(", "", CAT_CATEGORY_SPECIAL},
  {"lcm(a,b,...)", "lcm(", "", CAT_CATEGORY_CALCULUS},
  {"leading(p,x)", "leading(", "", CAT_CATEGORY_POLYNOMIAL},
  {"legendre(x,n,m)", "legendre(", "", CAT_CATEGORY_SPECIAL},
  {"mag(z)", "mag(", "", CAT_CATEGORY_COMPLEXNUM},
  {"mod(a,b)", "mod(", "", CAT_CATEGORY_CALCULUS},
  {"not(x)", "not(", "", CAT_CATEGORY_PROG},
  {"nroots(p,x)", "nroots(", "", CAT_CATEGORY_POLYNOMIAL},
  {"number(x)", "number(", "", CAT_CATEGORY_PROG},
  {"numerator(x)", "numerator(", "", CAT_CATEGORY_OTHER},
  {"or(a,b,...)", "or(", "", CAT_CATEGORY_PROG},
  {"outer(a,b,...)", "outer(", "", CAT_CATEGORY_LINEARALG},
  {"polar(z)", "polar(", "", CAT_CATEGORY_COMPLEXNUM},
  {"prime(n)", "prime(", "", CAT_CATEGORY_CALCULUS},
  {"print(a,b,...)", "print(", "", CAT_CATEGORY_PROG},
  {"product(i,j,k,f)", "product(", "", CAT_CATEGORY_PROG},
  {"quote(x)", "quote(", "", CAT_CATEGORY_OTHER},
  {"quotient(p,q,x)", "quotient(", "", CAT_CATEGORY_POLYNOMIAL},
  {"rank(a)", "rank(", "", CAT_CATEGORY_LINEARALG},
  {"rationalize(x)", "rationalize(", "", CAT_CATEGORY_OTHER},
  {"real(z)", "real(", "", CAT_CATEGORY_COMPLEXNUM},
  {"rect(z)", "rect(", "", CAT_CATEGORY_COMPLEXNUM},
  {"roots(p,x)", "roots(", "", CAT_CATEGORY_POLYNOMIAL},
  {"sgn(x)", "sgn(", "", CAT_CATEGORY_OTHER},
  {"simplify(x)", "simplify(", "", CAT_CATEGORY_OTHER},
  {"sin(x)", "sin(", "", CAT_CATEGORY_TRIG},
  {"sinh(x)", "sinh(", "", CAT_CATEGORY_TRIG},
  {"stop()", "stop()", "", CAT_CATEGORY_PROG},
  {"subst(a,b,c)", "subst(", "", CAT_CATEGORY_OTHER},
  {"sum(i,j,k,f)", "sum(", "", CAT_CATEGORY_PROG},
  {"tan(x)", "tan(", "", CAT_CATEGORY_TRIG},
  {"tanh(x)", "tanh(", "", CAT_CATEGORY_TRIG},
  {"taylor(f,x,n,a)", "taylor(", "", CAT_CATEGORY_CALCULUS},
  {"test(a,b,c,d,...)", "test(", "", CAT_CATEGORY_PROG},
  {"transpose(a,i,j)", "transpose(", "", CAT_CATEGORY_LINEARALG},
  {"unit(n)", "unit(", "", CAT_CATEGORY_LINEARALG},
  {"zero(i,j,...)", "zero(", "", CAT_CATEGORY_LINEARALG},
  {">", ">", "", CAT_CATEGORY_PROG},
  {"<", "<", "", CAT_CATEGORY_PROG}
};

int showCatalog(char* insertText) {
  int ret;
  // returns 0 on failure (user exit) and 1 on success (user chose a option)
  MenuItem menuitems[9];
  menuitems[0].text = (char*)"All";
  menuitems[1].text = (char*)"Complex number";
  menuitems[2].text = (char*)"Linear algebra";
  menuitems[3].text = (char*)"Calculus";
  menuitems[4].text = (char*)"Polynomial";
  menuitems[5].text = (char*)"Special";
  menuitems[6].text = (char*)"Program and logic";
  menuitems[7].text = (char*)"Trigonometry";
  menuitems[8].text = (char*)"Other";
  
  Menu menu;
  menu.items=menuitems;
  menu.numitems=9;
  menu.scrollout=1;
  menu.title = (char*)"Function Catalog";
  
  int incat = 1;
  while(incat) {
    int sres = doMenu(&menu);
    ret=0;
    if(sres == MENU_RETURN_SELECTION) {
      if(doCatalogMenu(insertText, menuitems[menu.selection-1].text, menu.selection-1)) {
        ret=1;
        incat = 0;
      }
    } else {
      incat = 0;
    }
  }
  return ret;
}

// 0 on exit, 1 on success
int doCatalogMenu(char* insertText, char* title, int category) {
  MenuItem* menuitems = (MenuItem*)alloca(sizeof(MenuItem)*CAT_COMPLETE_COUNT);
  int cur = 0; int curmi = 0;
  while(cur<CAT_COMPLETE_COUNT) {
    if(completeCat[cur].category == category || category == CAT_CATEGORY_ALL) {
      menuitems[curmi].type = MENUITEM_NORMAL;
      menuitems[curmi].color = TEXT_COLOR_BLACK;
      menuitems[curmi].isfolder = cur; // little hack: store index of the command in the full list in the isfolder property (unused by the menu system in this case)
      menuitems[curmi].text = completeCat[cur].name;
      curmi++;
    }
    cur++;
  }
  
  Menu menu;
  menu.items=menuitems;
  menu.numitems=curmi;
  menu.scrollout=1;
  menu.title = title;
  int sres = doMenu(&menu);
  if(sres == MENU_RETURN_SELECTION) {
    strcpy(insertText, completeCat[menuitems[menu.selection-1].isfolder].insert);
    return 1;
  }
  return 0;
}