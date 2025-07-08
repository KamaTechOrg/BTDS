# BooTcampDataStructures

הערה חשובה ביותר לכותבות ב C : 

לכל מבנה נתונים (LL DLL STR ARR וכו' ) יש פונקציה בשם ToString שמקבלת פוינטר למבנה נתונים. דהיינו:

char* ARR_ToString(const ARR* arr);

char* LL_ToString(const LL* list);  
  
וכו'

כמובן צריך לעשות free ל * char שחוזר. אבל ככה אפשר עם printf להדפיס כל מבנה נתונים שהוא. 
