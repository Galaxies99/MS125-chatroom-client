### Chat Room 用户手册

####  Part 1  运行客户端

运行 "chatroomClient.exe" 即可进入聊天室登陆界面。

#### Part 2  登陆界面

如果您想直接退出程序，点击 Exit 按钮即可。

如果您想要注册新用户，点击 Register 按钮，转到 "Part 3  注册界面"。

如果您想要以游客的身份登陆，直接点击 Login 按钮即可，转到 "Part 4  聊天界面"。

- Tips: 以游客身份登陆将不能享受某些功能，且所有游客共用同一个用户名 Tourist。

如果您是已经注册的用户，需要登陆到聊天室，则：

1. 在用户名 (User Name) 和密码 (Password) 文本框内分别输入您的用户名和密码；
2. 你可以点击 "显示密码 (Display Password)" 复选框来显示您输入的密码；
3. 输入完毕后，点击 Login 即可发送登陆请求。

点击 Login 后，如果跳出聊天窗口，则说明登陆成功，转到 "Part 4  聊天界面"。

若出现错误提示，则相对应提示信息的可能情况对应如下：

| 提示信息                                                     | 对应情况                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Invalid username!                                            | 您输入的用户名长度不在3~256之间，或含除字母和数字外的特殊字符，或为 "Tourist" （被保留的游客用户名）。 |
| Invalid password: Password should have length between 1 and 16! | 您输入的密码长度不在1~16之间。                               |
| Invalid password: Password should not include \'#\'!         | 您输入的密码包含了 '#' 字符（密码不可以包含 \'#\' 字符）。   |
| Invalid username: No such user!                              | 您输入的用户名不存在。                                       |
| Invalid password: Wrong PassWord!                            | 您输入的用户名和密码不匹配。                                 |
| Something bad happens.                                       | 程序异常（此时推荐您反馈结果，以便于我们进行修复）。         |

#### Part 3  注册界面

如果你想返回登录界面，点击 Back 按钮即可。

如果你想要注册新用户，则

1. 在用户名 (User Name) 和密码 (Password) 文本框内分别输入您的用户名和密码；
2. 在重复密码 (Confirm Password) 文本框内重复您输入的密码；
3. 你可以点击 "显示密码 (Display Password)" 复选框来显示您两次输入的密码；
4. 输入完毕后，点击 Register 即可发送注册请求。

点击 Register 后，如果返回了登陆窗口，则说明登陆成功，转到 "Part 2  登陆界面"进行登陆操作即可。

若出现错误提示，则相对应提示信息的可能情况对应如下：

| 提示信息                                                     | 对应情况                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Invalid username!                                            | 您输入的用户名长度不在3~256之间，或含除字母和数字外的特殊字符，或为 "Tourist" （被保留的游客用户名）。 |
| Invalid password: Password should have length between 1 and 16! | 您输入的密码长度不在1~16之间。                               |
| Invalid password: Password should not include \'#\'!         | 您输入的密码包含了 '#' 字符（密码不可以包含 \'#\' 字符）。   |
| Invalid password: Password does not match!                   | 您两次输入的密码不匹配。                                     |
| Invalid username: Username existed!                          | 您输入的用户名已经存在。                                     |

#### Part 4  聊天界面

该界面上方是一个 Dialog 显示框，显示聊天记录；下方 Your Text 为输入框，您可以在输入框输入聊天信息后，点击 "Send Message!" 按钮发送。

在开始聊天之前，务必**点击上方菜单栏的 Basics ，选择 Connect to Server 以连接到服务器**，否则您发送的消息将不会被传输给其他用户。

当您连接到服务器之后，如果您不是以游客身份登陆，则输入框右上角将会出现您的等级以及金币，您可以通过聊天提升等级以及金币数量。

如果您不是以游客身份登陆，且想要修改用户名、密码，点击上方菜单栏的 Basics ，选择 Change Account ，转到 "Part 5  修改帐户界面"。

聊天记录显示框中的消息有如下几类（斜体表示可以替换成其他相似文本）：

| 显示消息                                              | 实际意义                                      |
| ----------------------------------------------------- | --------------------------------------------- |
| You: *text*                                           | 你发送了 *text* 这条消息                      |
| Tourist: *text*                                       | 某一个游客发送了 *text* 这条消息。            |
| *example* (Level *5*): *text*                         | *5* 级用户 *example* 发送了 *text* 这条消息。 |
| < *example* > log in.                                 | 用户 *example* 登陆了聊天室。                 |
| < *example* > log out.                                | 用户 *example* 离开了聊天室。                 |
| < *example1* > change his/her name to < *example2* >. | 用户 *example1* 修改了用户名为 *example2* 。  |

#### Part 5  修改帐户界面

如果你想返回聊天界面，点击 Back 按钮即可。

如果你想要修改用户信息，则

1. 在旧用户名 (Old User Name) 和密码 (Password) 文本框内分别输入当前您的用户名和密码；
2. 在新用户名 (New User Name) 和新密码 (New Password) 文本框分别输入您需要修改的用户名和密码；
   - 注意：如果您不需要修改密码，则需要在新密码处输入原来的密码。
3. 你可以点击 "显示密码 (Display Password)" 复选框来显示您的新旧密码；
4. 输入完毕后，点击 Change 即可发送修改信息请求。

点击 Change 后，如果返回了聊天窗口，则说明修改信息成功，转到 "Part 4  聊天界面"进行聊天即可。

修改个人信息后，**您的等级以及金币数将被保留**。

若出现错误提示，则相对应提示信息的可能情况对应如下：

| 提示信息                                                     | 对应情况                                                     |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Invalid username!                                            | 您输入的用户名（新用户名或旧用户名）长度不在3~256之间，或含除字母和数字外的特殊字符，或为 "Tourist" （被保留的游客用户名），或新用户名和旧用户名相同。 |
| Invalid username: You can only change your account!          | 您输入的用户名不是您当前登陆的用户，您只能修改当前登陆用户的个人信息。 |
| Invalid password: Password should have length between 1 and 16! | 您输入的密码长度不在1~16之间。                               |
| Invalid password: Password should not include \'#\'!         | 您输入的密码包含了 '#' 字符（密码不可以包含 \'#\' 字符）。   |
| Invalid username: No such user!                              | 您输入的用户名不存在。                                       |
| Invalid password: Wrong Password!                            | 您输入的当前的用户名和密码不匹配。                           |
| Invalid username: Username existed!                          | 您输入的新用户名已被注册。                                   |