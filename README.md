1\. Adicionar alterações para commit:

&nbsp;  git add <ficheiro>   # adicionar ficheiro específico

&nbsp;  git add .            # adicionar todos os ficheiros modificados



2\. Fazer commit das alterações:

&nbsp;  git commit -m "Mensagem do commit"



3\. Enviar alterações para o repositório remoto: !PARA MANDAR AS TUAS MODIFCACOES NO PC PAR AO REPOSTIRIO



&nbsp;  git push origin main



4\. Trazer as últimas alterações do repositório remoto: !SEMPRE QUE HA MODIFICACOES NO REPOSITORIO E NAO NO TEU PC

&nbsp;  git pull origin main



5\. Criar nova branch (opcional):

&nbsp;  git checkout -b <nome\_branch>



6\. Mudar para uma branch existente (opcional):

&nbsp;  git checkout <nome\_branch>

git fetch origin main
git reset --hard origin/main