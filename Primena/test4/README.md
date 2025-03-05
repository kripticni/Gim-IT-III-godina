# Test za 6.3.2025.
## Polinomi
**Predstavljanje:**

**Polinomi** se prikazuju kao vektori (nizovi)
koeficienata:
```octave
	3x^2 + 5x + 1
	[3 5 1]
	#kada nemamo neki stepej, njegov koeficient je nula
	3x^4 + 5x + 1
	[3 0 0 5 1]
```

Da bi smo izracunali Y za neki X u polinomu:
```octave
	p = [3 0 0 5 1]
	x = 4
	y = polyval(p, x)
```
Da bi smo grafirali funkciju, samo moramo da
znamo opseg X (i korak):
```octave
	p = [3 0 0 5 1]
	x = [ -1.5:0.01:7 ]
	y = polyval(p,x)
```

Resenja ili nule polinoma dobijamo ovako:
```octave
	p = [3 0 0 5 1]
	r = roots(p)
```

A kada znamo resenja polinoma mozemo
da iz njih izrazimo i polinom:
```octave
	p = poly(r)
```

Ako hocemo da saberemo ili oduzmemo polinome, 
oni moraju da budu iste duzine sto znaci dopunjavamo
nulama sve dok nisu:
```octave
	p1=[3 15 0 -10 -3 15 -40];
	p2=[3 0 -2 -6];
	p=p1+[0 0 0 p2]
```

**Operacije:**
Da bi smo pomnozili ili podelili, koristimo 
operacije **konvolucije** (nacin kombinovanja
koeficienta dva vektora, da bi smo dobili treci):
```octave
	# conv za mnozenje, deconv za deljenje
	a=[3 15 0 -10 -3 15 -40];
	b=[3 0 -2 -6];
	c = conv(a,b)
	
	# a -> brojilac
	# b -> imenilac
	# c -> rezultat
	# o -> ostatak
	[c o] = deconv(a,b)
```



**Polyder** funkcija za izvode
ima nekoliko overload-a:
```octave
	# 1. izracunavanje izvoda jednog polinoma
	c = polyder(a)
	
	# 2. izvod proizvoda dva polinoma
	c = polyder (a, b)
	
	# 3. izvod kolicnika
	[c d] = polyder(a, b)
	(c -> brojioc, d -> imenioc
	a -> brojioc, b -> imenioc)
```

Za aproksimiranje koristimo **polyfit**
aproksimiranje je odredjivanje najblize
funkcije n-tog stepena koja prolazi kroz
tacke x, y (ili barem blizu):
```octave
	x = [1 2 3 4]
	y = [4 3 2 1]
	n = 1
	p = polyfit(x,y,n)
	dobili bi -x+5 donosno [-1 5]
```

## Trodimenzionalni grafikoni

Za ovu oblast je bitno da se podsetimo 
postojecih svojstva za 2d grafove od 
proslih testova i takodje funkcija:
- linspace
- exp
- log
- plot

**Grafikoni:**

Za grafikon trece dimenzije:
plot3(x,y,z,*svojstva...*)
crta liniju koja povezuje sve tacke u 3d:
```octave
	# ako znamo da su parametri
	x=cos(2t)
	y=cos(2t)
	z=0.5t
	0 =< t =< 6\*pi
	# onda mozemo da izgrafiramo ovako
	t=0:0.1:6\*pi;
	x=sqrt(t).\*sin(2\*t);
	y=sqrt(t).\*cos(2\*t);
	z=0.5.*t;
	plot3(x,y,z,'r','linewidth',2)
	grid on
	xlabel('x'),ylabel('y'),zlabel('z')
```

Postoje i mrezasti i povrsinski 3d grafikoni
oni su predstavljeni kao:
```octave
	z=f(x,y)
	# 1. prvo biramo opseg za x, y nezavisno
	x=-1:3
	y=1:4
	# 2. pravimo matricu koja pokriva sve tacke (x,y,0)
	[X,Y] = meshgrid(x,y)
	# 3. racunamo Z za svaku tacku (uzeto proizvoljna f-ija)
	Z= X.* Y.^2 ./ (X.^2 + Y.^2)
	# 4. prikazujemo mesoviti ili povrsinski
	mesh(X,Y,Z)
	# ili
	# surf(X,Y,Z)
```

| Vrsta grafikona | Komanda |
|-----------------|---------|
| Konturni 2D     | `contour` |
| Konturni 3D     | `contour3` |
| Grafikon diskretnih podataka 3D | `stem3` |
| Tačkasti 3D     | `scatter3` |
| Kružni 3D       | `pie` |

primer za kruzni:
```octave
	x=[5 9 14 20];
	explode=[0 0 1 0]; # odredjuje udaljenost odsecka od centra
	pie3(x,explode)
```

**View, subplot i interpoliranje**

**View** odredjuje pravac posmatranja uz pomocu
azimuta i elevacije, ili u obliku tacke iz koje se posmatra
1. view(az,el)
2. view([x,y])
**azimut** - pomeranje tacke gledista sfericno i horizontalno u
odnosu na tacku posmatranja od 0 do 360
**elevacija** - isto kao azimut ali vertikalno, i od -90 do 90


| Ravan na koju se projektuje | Ugao az (°) | Ugao el (°) |
|-----------------------------|------------|------------|
| X – Y (pogled odozgo)       | 0          | 90         |
| X – Z (bočni pogled)        | 0          | 0          |
| Y – Z (bočni pogled)        | 90         | 0          |

**Interpoliranje** je izracunavanje vrednosti
izmedju dve poznate tacke, 1d je ono kod
koga svakoj tacki odgovara jedna nezavisna x
i jedna zavisna y
yi = interp1(x,y,xi,'metoda')
yi -> interpolirana vrednost
xi -> horizontalna kordinata tacke koja se interpolira
x -> x vektor koordinata
y -> y vektor koordinata
metoda -> linear (linearna), spline (kubna)

**Subplot** je funcija koja nam omogucava da
prikazemo nekoliko grafova u istom
prozoru

subplot(vrsta, kolona, indeks)
Subplot 2x3 ima ove indekse
```
+----+-----+----+
|  1 |  2  |  3 |
+----+-----+----+
|  4 |  5  |  6 |
+----+-----+----+
```

Ako hocemo da stavimo graf na koordinatama (2,3)
u subplotu dimenzija 2x3, onda stavljamo
subplot(2,3,6)

primer ovih funkcija:
```octave
	x=0:1:5;
	y=[1 -0.6242 -1.4707 3.2406 -0.7366 -6.3717];
	xi=0:1:5;
 	
	yilin=interp1(x,y,xi,'linear');
	yispl=interp1(x,y,xi,'spline');
 
	yfun=1.5.^xi.*cos(2*x);
	 
	subplot(1,2,1), plot(x,y,'*',xi,yilin,xi,yfun,'--')
	subplot(1,2,2), plot(x,y,'*',xi,yispl,xi,yfun,'--')
```
