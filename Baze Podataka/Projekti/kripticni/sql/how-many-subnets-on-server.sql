SELECT javna_addr, COUNT(podmreze.gateway_addr) 
FROM mreze JOIN podmreze USING(javna_addr)
           JOIN serveri USING(javna_addr)
GROUP BY javna_addr;
