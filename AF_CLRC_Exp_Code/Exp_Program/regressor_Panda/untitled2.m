
clear
clc
filetext = readlines('regressor.txt');
for i=1:length(filetext)
    for k=6:-1:0
        for j=63:-1:0
            filetext(i)=replace(filetext(i), ['(',num2str(k),',',num2str(j),')'], ['(',num2str(k+1),',',num2str(j+1),')']);
        end
        %         filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
        filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
        %     replace(filetext, ['ddq(',num2str(k),')'], ['ddq(',num2str(k+1),')']);
        %     replace(filetext, ['H(',num2str(k),')'], ['H(',num2str(k+1),')']);
    end

end

% for i=length(filetext):-1:1
%     filetext(i)=replace(filetext(i), [num2str((i-1)/2),','], ['par(',num2str((i-1)/2+1),')=']);
%     for k=6:-1:0
%         filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
%     end
% end

% filetext=replace(filetext, ',', ";\n");
% filetext=replace(filetext, '[', "");filetext=replace(filetext, ']', "");
% fprintf(filetext)

% str1=['x','y','z'];
% str2=['xx';'xy';'xz';'yy';'yz';'zz'];
%
%
% for k=1:7
%
%     fprintf(['fc_',num2str(k),'=panda_par(',num2str(77+k),');']);
%
% end