# 出力の変換についての説明
output_converter.cpp で txt 形式から ndl 形式に変換する  
output_converter.cpp のファイル入力およびファイル出力は仮の名前なので適宜変更してください  
その際 txt ファイルは以下の形式で出力する  

(コマンド1)  

(コマンド2)  

...  

(コマンドm)  

ただし、 コマンドは以下の形式で出力し, 最後のコマンドは必ず Halt でなければならない  

終了: "Halt"  

待機: "Wait"  

重力切り替え: "Flip"  

*dir*(∈{'x','y','z'}) 方向へキョリ *lld* 直線移動: "SMove *dir* *lld*"  

*dir1*(∈{'x','y','z'}) 方向へキョリ *sld1* 移動した後 *dir2*(∈{'x','y','z'}) 方向へキョリ *sld2* 移動 L字移動: "LMove *dir1* *sld1* *dir2* *sld2*"  

(*dx*,*dy*,*dz*)(∈{-1,0,1}^3) 方向に *m* 個の seed を渡す 分裂: "Fission *dx* *dy* *dz* *m*"  

voxel に物質を生成し (*dx*,*dy*,*dz*)(∈{-1,0,1}^3) 方向に移動 物質生成: "Fission *dx* *dy* *dz*"  

(*dx*,*dy*,*dz*)(∈{-1,0,1}^3) 方向にいる S と融合する Pが行う融合: "FusionP *dx* *dy* *dz*"  

(*dx*,*dy*,*dz*)(∈{-1,0,1}^3) 方向にいる P と融合する Sが行う融合: "FusionS *dx* *dy* *dz*"  