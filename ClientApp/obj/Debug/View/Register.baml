   M S B A M L   `   `   `  ����D  @ClientApp, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:ClientApp.ViewClientApp.View  5   	       ClientApp.View.Register   5   	   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:ClientApp.View     5   	     � WindowStartupLocation$  CenterOwner=�5   	    � 
ResizeMode$ NoResize=�5	   	    � Title$ Register��5
   	   $	��300��6   $	��400��6'   .��5      �  � RowDefinitions 5   
   �� 5      �� 5      �� 5      �� 5      �� 5      .+�5   
   �� -   5         ��Name$ usernameTxt��5   4   $��Center=�6   $��0��6I   $	��250��6V   $��30��6e   �� 5   
   -   5         ��Name$ 
usernamePh��5      $��Username��6$   $	��250��67   $��30��6F   
������� J� IsHitTestVisible .  6g   �� 5   
   -   5        $ emailTxt��5   4   $��Center=�6   $��1��6F   $	��250��6S   $��30��6b   �� 5   
   -   5        $ emailPh��5      $��1��6!   $��Email��6.   $	��250��6>   $��30��6M   
������� .  6n   G� 5   
   -   5         G�Name$ passwordTxt��5   8   $��Center=�6   $��2��6M   $	��250��6Z   $��30��6i   �� 5   
   -   5        $ 
passwordPh��5      $��2��6$   $��Password��61   $	��250��6D   $��30��6S   
������� .  6t   G� 5   
   -   5        $ passwordAgainTxt��5   8   $��Center=�6   $��3��6R   $	��250��6_   $��30��6n   �� 5   
   -   5        $ passwordAgainPh��5      $��3��6)   $��Password again��66   $	��250��6O   $��30��6^   
������� .  6   �� 5   
   -	   5         ��Name$ 	cancelBtn��5      $��4��6$   $��Cancel��61   $��30��6B   $��90��6N   $
��Left=�6Y   $��10q�6t   �� 5   
   -
   5        $ registerBtn��5      $��4��6&   $��Register��63   $��30��6F   $	��100��6R   $��Right=�6^   $��10q�6z   5      5      