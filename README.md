# Implementação da Árvore B parra solucionar problema da clínica

Um atendimento é visto como uma relação de um paciente, a um terapeuta, num dia e horário e local determinado.

O atendimento pode ter ocorrido com sucesso. Ou, em outros casos, ter sido, cancelado, adiado, não ocorrido por ausência do terapeuta, não ocorrido por ausência do paciente, não ocorrido por questões outras.

Continuando a ideia do trabalho anterior. Imagina que a quantidade de atendimento em um ano é muito grande. Visto que em cada consultório há uma capacidade de atendimento diário de 10 consultas. Assim, seriam 50 atendimentos por dia, e aproximadamente 250 atendimentos numa semana. 

Em 50 semanas (quase 1 ano), necessitaríamos registrar 12500 atendimentos. Obviamente que não será possível armazenas todas os atendimentos em memória principal. Portanto, deve-se usar a ideia de armazenamento em memória secundária. Também não será possível colocar todos os atendimentos em uma árvore binária. Visto que seriam necessárias, no mínimo, 15 consultas para chegar a uma informação.

Assim, deve-se pensar numa solução em árvore B (B, B+ ou B*) que não ultrapasse 3 níveis.

Deve ter em mente que faremos buscas para verificar a situação de um determinado atendimento.

Para este exercício, pede-se que se gere de forma aleatória (criar uma função específica para isso) um determinado número de atendimentos. (este número deve ser passado por parâmetro).

Lembrar que usaremos esta implementação para realizar o terceiro trabalho, que será sobre estatísticas sobre a base de dados gerada.
