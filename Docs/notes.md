Modelo LitGen 

* É um modelo multi-level, e portanto é representado por uma cadeia de markov;

* Session-level: A sessão consiste em um periodo largo de uso da rede, na qual um usuario pode realizar a transferencia de diversos objetos. É composto por uma sequancia de tempos de sessão, e inter-sessão. As variaveis aleatorias são:
    * N_session: numero de objetos transferidos durante uma sessão
    * T_is: tempo inter-sessão
    * Para clusterização dos objetos em sessões, foi definido um limiar de 300 segundos

* Object-level: um objeto transferido pode ser várias coisas: uma imagem, uma playlist de musicas, uma pagina web, etc.. A transferência de um objeto se da por varias requisições e respostas. As variabeis aleatorias são:
    * N_obj: numero de pacotes de um objeto
    * IA_obj: tempos entre a transferências de objetos dentro de uma sessão. 
    * Para classificar os objetos, utilizamos as flags TCP: SYN, FIN, ...

* Packet-level: 