# Participantes do projeto
Aldo Queiroz Cabral da Fonseca Tinoco
Felipe Augusto Lemos Barreto
João Pedro Silva de Fontes Pereira

# Compilação 

Basta rodar o seguinte comando no terminal para realizar a compilação:  
g++ Main.cpp Base.h Base.cpp Game.cpp Game.h Player.cpp Player.h Bullet.h Bullet.cpp Enemy.cpp Enemy.h Ammo.h Ammo.cpp EnemyBullet.h EnemyBullet.cpp Health.h Health.cpp -o jogo -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
Em seguida, rodar: ./jogo

OBS: É necessário ter a biblioteca SFML instalada em algum repositório padrão da sua máquina.
Link para instalar o SFML: https://www.sfml-dev.org/download/sfml/2.6.1/
# Recursos implementados  

Movimentação do WASD (Frente, esquerda, trás e direita, respectivamente)  
Disparo no Q  
Botão de pausa no P  
Botão de reiniciar no R  
Inimigos atiram na direção do jogador  
Inimigos tem chance de soltar munição para o jogador e vida para a base ao serem eliminados
Incremento de dificuldade: Mais inimigos surgem à medida que o player ganha pontos
O jogo finaliza quando o player alcança 150 pontos

# Referências aos sprites

https://www.flaticon.com/br/icone-gratis/tacos_5787109  
https://www.flaticon.com/br/icone-gratis/cranio_581735  
https://www.flaticon.com/br/icone-gratis/inimigo_1477179  
https://www.pngegg.com/en/png-wdpyr  
https://www.flaticon.com/br/icone-gratis/taco_3946536  
