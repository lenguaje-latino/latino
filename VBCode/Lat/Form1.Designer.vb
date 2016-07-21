<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.ArchivoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NuevoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AbrirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GuardarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem1 = New System.Windows.Forms.ToolStripSeparator()
        Me.ImprimirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripSeparator()
        Me.SalirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EditarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopiarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CortarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PegarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem3 = New System.Windows.Forms.ToolStripSeparator()
        Me.DeshacerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RehacerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStripMenuItem4 = New System.Windows.Forms.ToolStripSeparator()
        Me.SeleccionarTodoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopiarTodoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LimpiarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.HerramientasToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ImprimirFechaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LineasToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.TotalToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AcercaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GitHubToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SoporteToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SitioWebToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SaveFileDialog1 = New System.Windows.Forms.SaveFileDialog()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.FontDialog1 = New System.Windows.Forms.FontDialog()
        Me.PrintDialog1 = New System.Windows.Forms.PrintDialog()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.MenuStrip1.SuspendLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'RichTextBox1
        '
        Me.RichTextBox1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.RichTextBox1.Font = New System.Drawing.Font("Times New Roman", 12.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.RichTextBox1.Location = New System.Drawing.Point(34, 27)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.Size = New System.Drawing.Size(508, 462)
        Me.RichTextBox1.TabIndex = 0
        Me.RichTextBox1.Text = ""
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ArchivoToolStripMenuItem, Me.EditarToolStripMenuItem, Me.HerramientasToolStripMenuItem, Me.AcercaToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(542, 24)
        Me.MenuStrip1.TabIndex = 1
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'ArchivoToolStripMenuItem
        '
        Me.ArchivoToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NuevoToolStripMenuItem, Me.AbrirToolStripMenuItem, Me.GuardarToolStripMenuItem, Me.ToolStripMenuItem1, Me.ImprimirToolStripMenuItem, Me.ToolStripMenuItem2, Me.SalirToolStripMenuItem})
        Me.ArchivoToolStripMenuItem.Name = "ArchivoToolStripMenuItem"
        Me.ArchivoToolStripMenuItem.Size = New System.Drawing.Size(60, 20)
        Me.ArchivoToolStripMenuItem.Text = "Archivo"
        '
        'NuevoToolStripMenuItem
        '
        Me.NuevoToolStripMenuItem.Name = "NuevoToolStripMenuItem"
        Me.NuevoToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.N), System.Windows.Forms.Keys)
        Me.NuevoToolStripMenuItem.Size = New System.Drawing.Size(161, 22)
        Me.NuevoToolStripMenuItem.Text = "Nuevo"
        '
        'AbrirToolStripMenuItem
        '
        Me.AbrirToolStripMenuItem.Name = "AbrirToolStripMenuItem"
        Me.AbrirToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.O), System.Windows.Forms.Keys)
        Me.AbrirToolStripMenuItem.Size = New System.Drawing.Size(161, 22)
        Me.AbrirToolStripMenuItem.Text = "Abrir"
        '
        'GuardarToolStripMenuItem
        '
        Me.GuardarToolStripMenuItem.Name = "GuardarToolStripMenuItem"
        Me.GuardarToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.S), System.Windows.Forms.Keys)
        Me.GuardarToolStripMenuItem.Size = New System.Drawing.Size(161, 22)
        Me.GuardarToolStripMenuItem.Text = "Guardar"
        '
        'ToolStripMenuItem1
        '
        Me.ToolStripMenuItem1.Name = "ToolStripMenuItem1"
        Me.ToolStripMenuItem1.Size = New System.Drawing.Size(158, 6)
        '
        'ImprimirToolStripMenuItem
        '
        Me.ImprimirToolStripMenuItem.Name = "ImprimirToolStripMenuItem"
        Me.ImprimirToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.P), System.Windows.Forms.Keys)
        Me.ImprimirToolStripMenuItem.Size = New System.Drawing.Size(161, 22)
        Me.ImprimirToolStripMenuItem.Text = "Imprimir"
        '
        'ToolStripMenuItem2
        '
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        Me.ToolStripMenuItem2.Size = New System.Drawing.Size(158, 6)
        '
        'SalirToolStripMenuItem
        '
        Me.SalirToolStripMenuItem.Name = "SalirToolStripMenuItem"
        Me.SalirToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.W), System.Windows.Forms.Keys)
        Me.SalirToolStripMenuItem.Size = New System.Drawing.Size(161, 22)
        Me.SalirToolStripMenuItem.Text = "Salir"
        '
        'EditarToolStripMenuItem
        '
        Me.EditarToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.CopiarToolStripMenuItem, Me.CortarToolStripMenuItem, Me.PegarToolStripMenuItem, Me.ToolStripMenuItem3, Me.DeshacerToolStripMenuItem, Me.RehacerToolStripMenuItem, Me.ToolStripMenuItem4, Me.SeleccionarTodoToolStripMenuItem, Me.CopiarTodoToolStripMenuItem, Me.LimpiarToolStripMenuItem})
        Me.EditarToolStripMenuItem.Name = "EditarToolStripMenuItem"
        Me.EditarToolStripMenuItem.Size = New System.Drawing.Size(49, 20)
        Me.EditarToolStripMenuItem.Text = "Editar"
        '
        'CopiarToolStripMenuItem
        '
        Me.CopiarToolStripMenuItem.Name = "CopiarToolStripMenuItem"
        Me.CopiarToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.C), System.Windows.Forms.Keys)
        Me.CopiarToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.CopiarToolStripMenuItem.Text = "Copiar"
        '
        'CortarToolStripMenuItem
        '
        Me.CortarToolStripMenuItem.Name = "CortarToolStripMenuItem"
        Me.CortarToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.X), System.Windows.Forms.Keys)
        Me.CortarToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.CortarToolStripMenuItem.Text = "Cortar"
        '
        'PegarToolStripMenuItem
        '
        Me.PegarToolStripMenuItem.Name = "PegarToolStripMenuItem"
        Me.PegarToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.V), System.Windows.Forms.Keys)
        Me.PegarToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.PegarToolStripMenuItem.Text = "Pegar"
        '
        'ToolStripMenuItem3
        '
        Me.ToolStripMenuItem3.Name = "ToolStripMenuItem3"
        Me.ToolStripMenuItem3.Size = New System.Drawing.Size(201, 6)
        '
        'DeshacerToolStripMenuItem
        '
        Me.DeshacerToolStripMenuItem.Name = "DeshacerToolStripMenuItem"
        Me.DeshacerToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Z), System.Windows.Forms.Keys)
        Me.DeshacerToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.DeshacerToolStripMenuItem.Text = "Deshacer"
        '
        'RehacerToolStripMenuItem
        '
        Me.RehacerToolStripMenuItem.Name = "RehacerToolStripMenuItem"
        Me.RehacerToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.Y), System.Windows.Forms.Keys)
        Me.RehacerToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.RehacerToolStripMenuItem.Text = "Rehacer"
        '
        'ToolStripMenuItem4
        '
        Me.ToolStripMenuItem4.Name = "ToolStripMenuItem4"
        Me.ToolStripMenuItem4.Size = New System.Drawing.Size(201, 6)
        '
        'SeleccionarTodoToolStripMenuItem
        '
        Me.SeleccionarTodoToolStripMenuItem.Name = "SeleccionarTodoToolStripMenuItem"
        Me.SeleccionarTodoToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.A), System.Windows.Forms.Keys)
        Me.SeleccionarTodoToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.SeleccionarTodoToolStripMenuItem.Text = "Seleccionar todo"
        '
        'CopiarTodoToolStripMenuItem
        '
        Me.CopiarTodoToolStripMenuItem.Name = "CopiarTodoToolStripMenuItem"
        Me.CopiarTodoToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.CopiarTodoToolStripMenuItem.Text = "Copiar todo"
        '
        'LimpiarToolStripMenuItem
        '
        Me.LimpiarToolStripMenuItem.Name = "LimpiarToolStripMenuItem"
        Me.LimpiarToolStripMenuItem.ShortcutKeys = CType((System.Windows.Forms.Keys.Control Or System.Windows.Forms.Keys.T), System.Windows.Forms.Keys)
        Me.LimpiarToolStripMenuItem.Size = New System.Drawing.Size(204, 22)
        Me.LimpiarToolStripMenuItem.Text = "Limpiar"
        '
        'HerramientasToolStripMenuItem
        '
        Me.HerramientasToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ImprimirFechaToolStripMenuItem, Me.LineasToolStripMenuItem})
        Me.HerramientasToolStripMenuItem.Name = "HerramientasToolStripMenuItem"
        Me.HerramientasToolStripMenuItem.Size = New System.Drawing.Size(90, 20)
        Me.HerramientasToolStripMenuItem.Text = "Herramientas"
        '
        'ImprimirFechaToolStripMenuItem
        '
        Me.ImprimirFechaToolStripMenuItem.Name = "ImprimirFechaToolStripMenuItem"
        Me.ImprimirFechaToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F5
        Me.ImprimirFechaToolStripMenuItem.Size = New System.Drawing.Size(171, 22)
        Me.ImprimirFechaToolStripMenuItem.Text = "Imprimir fecha"
        '
        'LineasToolStripMenuItem
        '
        Me.LineasToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.TotalToolStripMenuItem})
        Me.LineasToolStripMenuItem.Name = "LineasToolStripMenuItem"
        Me.LineasToolStripMenuItem.Size = New System.Drawing.Size(171, 22)
        Me.LineasToolStripMenuItem.Text = "Lineas"
        '
        'TotalToolStripMenuItem
        '
        Me.TotalToolStripMenuItem.Name = "TotalToolStripMenuItem"
        Me.TotalToolStripMenuItem.Size = New System.Drawing.Size(101, 22)
        Me.TotalToolStripMenuItem.Text = "Total"
        '
        'AcercaToolStripMenuItem
        '
        Me.AcercaToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.GitHubToolStripMenuItem, Me.SoporteToolStripMenuItem, Me.SitioWebToolStripMenuItem})
        Me.AcercaToolStripMenuItem.Name = "AcercaToolStripMenuItem"
        Me.AcercaToolStripMenuItem.Size = New System.Drawing.Size(55, 20)
        Me.AcercaToolStripMenuItem.Text = "Acerca"
        '
        'GitHubToolStripMenuItem
        '
        Me.GitHubToolStripMenuItem.Name = "GitHubToolStripMenuItem"
        Me.GitHubToolStripMenuItem.Size = New System.Drawing.Size(122, 22)
        Me.GitHubToolStripMenuItem.Text = "GitHub"
        '
        'SoporteToolStripMenuItem
        '
        Me.SoporteToolStripMenuItem.Name = "SoporteToolStripMenuItem"
        Me.SoporteToolStripMenuItem.Size = New System.Drawing.Size(122, 22)
        Me.SoporteToolStripMenuItem.Text = "Soporte"
        '
        'SitioWebToolStripMenuItem
        '
        Me.SitioWebToolStripMenuItem.Name = "SitioWebToolStripMenuItem"
        Me.SitioWebToolStripMenuItem.Size = New System.Drawing.Size(122, 22)
        Me.SitioWebToolStripMenuItem.Text = "Sitio web"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'PrintDialog1
        '
        Me.PrintDialog1.UseEXDialog = True
        '
        'Timer1
        '
        '
        'PictureBox1
        '
        Me.PictureBox1.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.PictureBox1.BackColor = System.Drawing.Color.AliceBlue
        Me.PictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center
        Me.PictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.PictureBox1.Location = New System.Drawing.Point(0, 27)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(33, 462)
        Me.PictureBox1.TabIndex = 3
        Me.PictureBox1.TabStop = False
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(542, 490)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.RichTextBox1)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.Text = "Latino Editor - Sin título"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents RichTextBox1 As RichTextBox
    Friend WithEvents MenuStrip1 As MenuStrip
    Friend WithEvents ArchivoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents EditarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents NuevoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AbrirToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents GuardarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem1 As ToolStripSeparator
    Friend WithEvents ImprimirToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem2 As ToolStripSeparator
    Friend WithEvents SalirToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CortarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CopiarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents PegarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ToolStripMenuItem3 As ToolStripSeparator
    Friend WithEvents DeshacerToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents RehacerToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SaveFileDialog1 As SaveFileDialog
    Friend WithEvents OpenFileDialog1 As OpenFileDialog
    Friend WithEvents FontDialog1 As FontDialog
    Friend WithEvents PrintDialog1 As PrintDialog
    Friend WithEvents ToolStripMenuItem4 As ToolStripSeparator
    Friend WithEvents LimpiarToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SeleccionarTodoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents HerramientasToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents ImprimirFechaToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents CopiarTodoToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents Timer1 As Timer
    Friend WithEvents PictureBox1 As PictureBox
    Friend WithEvents LineasToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents TotalToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents AcercaToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SitioWebToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents GitHubToolStripMenuItem As ToolStripMenuItem
    Friend WithEvents SoporteToolStripMenuItem As ToolStripMenuItem
End Class
