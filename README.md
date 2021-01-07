<h1>Projeto 2 de Programação Concorrente e Distribuída</h1>

<h2>Atividade  1 - Seção Crítica por espera ocupada</h2>

<p> Nesta atividade foi realizada a implementação do controle de acesso a uma região critica empregando a abordagem Cliente-Servidor baseado no algoritimo de Manna-Pnueli. Nesta implementação processos cliente solicitam acesso a uma região critica ao processo servidor.</p> 

<h2>Atividade 2 - Somatórias, seção crítica e reduções em OpenMP</h2>
<p> Esta atividade realiza adaptações no código do Jogo da Vida realizado na atividade 1. As práticas atulizadas são:</p>
<ul>
  <li>#pragma omp critical</li>
  <li>#pragma omp for reduction(???)</li>
  <li>apenas recursos da linguagem C/C++, sem uso de semáforos e de diretivas de openMP</li>
</ul>

<h2>Atividade 3 - Seção crítica em Java</h2>

<p> Nesta atividade foi implementada uma modificação em um código que implementa uma interface onde podem ser inseridos carros nos dois sentidos de uma via de modo a permitir que os carros atravessem uma ponte um por vez evitando colisões. Considerando a ponte uma região crítica, foi implementado um semáforo binário com fila para controlar o acesso a ela.</p>
