namespace GUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.userControl11 = new GUI.UserControl1();
            this.userControl21 = new GUI.UserControl2();
            this.userControl31 = new GUI.UserControl3();
            this.userControl41 = new GUI.UserControl4();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.button3);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Left;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(172, 636);
            this.panel1.TabIndex = 0;
            // 
            // button3
            // 
            this.button3.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(67)))), ((int)(((byte)(76)))), ((int)(((byte)(94)))));
            this.button3.Font = new System.Drawing.Font("Microsoft Sans Serif", 23.25F);
            this.button3.Location = new System.Drawing.Point(0, 532);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(172, 104);
            this.button3.TabIndex = 2;
            this.button3.Text = "Credits";
            this.button3.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(67)))), ((int)(((byte)(76)))), ((int)(((byte)(94)))));
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 23.25F);
            this.button2.Location = new System.Drawing.Point(0, 110);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(172, 104);
            this.button2.TabIndex = 1;
            this.button2.Text = "Configure";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(67)))), ((int)(((byte)(76)))), ((int)(((byte)(94)))));
            this.button1.Font = new System.Drawing.Font("Microsoft Sans Serif", 25.25F);
            this.button1.Location = new System.Drawing.Point(0, 0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(172, 104);
            this.button1.TabIndex = 0;
            this.button1.Text = "Chat";
            this.button1.UseVisualStyleBackColor = false;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(59)))), ((int)(((byte)(66)))), ((int)(((byte)(82)))));
            this.panel2.Controls.Add(this.userControl11);
            this.panel2.Controls.Add(this.userControl21);
            this.panel2.Controls.Add(this.userControl31);
            this.panel2.Controls.Add(this.userControl41);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(172, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(1312, 636);
            this.panel2.TabIndex = 1;
            // 
            // userControl11
            // 
            this.userControl11.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userControl11.Location = new System.Drawing.Point(0, 0);
            this.userControl11.Name = "userControl11";
            this.userControl11.Size = new System.Drawing.Size(1312, 636);
            this.userControl11.TabIndex = 3;
            // 
            // userControl21
            // 
            this.userControl21.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userControl21.Location = new System.Drawing.Point(0, 0);
            this.userControl21.Name = "userControl21";
            this.userControl21.Size = new System.Drawing.Size(1312, 636);
            this.userControl21.TabIndex = 2;
            // 
            // userControl31
            // 
            this.userControl31.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userControl31.Location = new System.Drawing.Point(0, 0);
            this.userControl31.Name = "userControl31";
            this.userControl31.Size = new System.Drawing.Size(1312, 636);
            this.userControl31.TabIndex = 1;
            // 
            // userControl41
            // 
            this.userControl41.Dock = System.Windows.Forms.DockStyle.Fill;
            this.userControl41.Location = new System.Drawing.Point(0, 0);
            this.userControl41.Name = "userControl41";
            this.userControl41.Size = new System.Drawing.Size(1312, 636);
            this.userControl41.TabIndex = 0;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(46)))), ((int)(((byte)(52)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(1484, 636);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Name = "Form1";
            this.Text = "P2PChat";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private UserControl4 userControl41;
        private UserControl1 userControl11;
        private UserControl2 userControl21;
        private UserControl3 userControl31;
    }
}

