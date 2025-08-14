
clear
clc
filetext = readlines('tau_func_def.txt');
for i=1:length(filetext)
    for k=80:-1:0
        %         % for j=63:-1:0
        filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
    end
    %                 filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
    % %         % filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
    % %         % filetext(i)=replace(filetext, ['q(',num2str(k),')'], ['q(',num2str(k+1),')']);
    % %         % filetext(i)=replace(filetext, ['dq(',num2str(k),')'], ['dq(',num2str(k+1),')']);
    % %
    %     end
    %
    i
end

% for i=length(filetext):-1:1
%     filetext(i)=replace(filetext(i), [num2str((i-1)/2),','], ['par(',num2str((i-1)/2+1),')=']);
%     for k=6:-1:0
%         filetext(i)=replace(filetext(i), ['[',num2str(k),']'], ['(',num2str(k+1),')']);
%     end
% end



% filetext=replace(filetext, ',', [';','\n']);
% filetext=replace(filetext, '[', "");filetext=replace(filetext, ']', "");
% fprintf(filetext)

% str1=['x','y','z'];
% str2=['xx';'xy';'xz';'yy';'yz';'zz'];
%
%
% for k=1:43
%     for i=1:7
%         for j=1:6
%             filetext(k)=replace(filetext(k), ['_',num2str(i),str2(j,:)], ['_',str2(j,:),'(',num2str(i),')']);
%         end
%         for j=1:3
%             filetext(k)=replace(filetext(k), ['_',num2str(i),str1(j)], ['_',str1(j),'(',num2str(i),')']);
%         end
%         filetext(k)=replace(filetext(k), ['m_',num2str(i)], ['m','(',num2str(i),')']);
%     end
%     % fprintf(['fc_',num2str(k),'=panda_par(',num2str(77+k),');']);
%
% end
% filetext

