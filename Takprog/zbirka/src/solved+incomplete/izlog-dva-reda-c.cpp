#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>

struct knjiga{
  uint32_t boja;
  uint32_t visina;
  uint32_t br;
};

static void unos(uint32_t& n, uint32_t& i, knjiga (&a)[50000], knjiga (&b)[50000]){
  scanf("%u", &n);
  for(i = 0; i < n; ++i)
    scanf("%u", &a[i].boja); 
  for(i = 0; i < n; ++i)
    scanf("%u", &a[i].visina); 
  for(i = 0; i < n; ++i)
    scanf("%u", &b[i].boja); 
  for(i = 0; i < n; ++i)
    scanf("%u", &b[i].visina); 
}

static void swap(knjiga* a, knjiga* b){
  knjiga temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main() noexcept {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cerr.tie(nullptr);
  
  uint32_t n, i;
  uint32_t ia, ib;
  uint32_t sa, sb;
  uint32_t sai, sbi;
  knjiga a[50000];
  knjiga b[50000];

  unos(n, i, a, b);

  std::sort(a, a+n, [](const auto& a, const auto& b){
    return a.boja < b.boja;
  });
  std::sort(b, b+n, [](const auto& a, const auto& b){
    return a.boja < b.boja;
  });
  sb = 0;
  sa = 0;
  ia = 0;
  ib = 0;

  while(ia < n && ib < n){
    for(ia = sa; ia < n && a[ia].boja == a[ia+1].boja; ++ia);
    for(ib = sb; ib < n && b[ib].boja == b[ib+1].boja; ++ib);

    std::sort(a+sa, a+ia, [](const auto& a, const auto& b){
      return a.visina < b.visina;
    });
    std::sort(b+sb, b+ib, [](const auto& a, const auto& b){
      return a.visina < b.visina;
    });

    if(sa == sb && ia == ib) continue; //skipujemo sve, vec je uredjeno

    //uredjujemo levi visak tako sto
    //za one sa leve strane nalazimo visinu najblizu njima
    sai = sa;
    sbi = sb;
    if(sa == sb) goto skip_left;
    if(sai < sbi){
      do{
        knjiga* m = std::lower_bound(a+sai, a+ia, b[sai]);
        if(m > a+ia){
          printf("-");
          return 0;
        }
        --m; //prva knjiga koja je manja od b[sa]
        swap(m, &a[sai]);
        ++sai;
      }while(sai < sbi);
      std::sort(a+sai, a+ia, [](const auto& a, const auto& b){
        return a.visina < b.visina;
      });
      sa = sai; //novi levi kraj
    }else{
      do{
        knjiga* m = std::lower_bound(b+sbi, b+ib, a[sbi]);
        if(m > b+ib){
          printf("-");
          return 0;
        }
        --m; //prva knjiga manja od a[sb]
        swap(m, &a[sbi]);
        ++sbi;
      }while(sbi < sai);
      std::sort(b+sbi, b+ib, [](const auto& a, const auto& b){
        return a.visina < b.visina;
      });
      sb = sbi; //novi levi kraj
    }
    //sa = sai ogranicujemo za dalje uredjivanje
    //sb = sbi tako da se ove vrednosti ne uzmu u obzir
  skip_left:
    if(ia == ib) continue; //levo je vec sigurno uredjeno, ako je i desno onda je sve
    if(ia > ib)
      // prakticno je isti kod a mrzi me da pisem
  }
}
